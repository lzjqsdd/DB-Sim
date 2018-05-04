#include "preprocess.h"
#include "type.h"

#include <string>
#include <sstream>
#include <fstream>
#include <boost/filesystem.hpp>

namespace bf = boost::filesystem;

bool cmp(std::string const &arg_a, std::string const &arg_b) {
	    return arg_a.size() < arg_b.size() || (arg_a.size() == arg_b.size() && arg_a < arg_b);
}

PProcess::PProcess(const string& inpath, const string& pattern,
		const int &interval,const string& outpath, 
		vector<vector<int>>& paths, map<int,shared_ptr<Node>>& nodes,
        map<int,shared_ptr<Link>>& links):
	inpath(inpath),
	pattern(pattern),
	interval(interval),
	outpath(outpath),
    paths(paths),
	nodes(nodes),
    links(links){ 
        if(!bf::exists(outpath)) bf::create_directory(outpath);
}

vector<string> PProcess::getFilelist(const string& dirpath,const string& pattern){
	vector<string> filelist;
	if(bf::exists(dirpath)){
		if(bf::is_directory(dirpath)){
			for(auto&& x : bf::directory_iterator(dirpath)){
				//string filename = x.path().filename().string();
				string filename = x.path().string();
				if(filename.find(pattern) != string::npos) 
					filelist.push_back(filename); 
			}
		}
	}
	else{
		LOG_FATAL("data is not exits!!!");
		exit(0);
	}

	sort(filelist.begin(),filelist.end(),cmp);
	return filelist;
}

void PProcess::sampleByTime(const string& path, bool lastfile){

	try{
		fstream fin(path.c_str(),std::ifstream::in);
		string line;
		set<int> pre_inscene;
		int frame,num;
		while(std::getline(fin,line)){
			istringstream is(line);
			is >> frame >> num;

            int carid,type,linkid,pathid;
            double x,y,zh;
			set<int> cur_inscene;
			for(int i = 0; i < num; ++i){
				std::getline(fin,line);
                istringstream is(line);
                is >> carid >> x >> y >> type >> linkid >> zh >> pathid;
                //LOG_TRACE(my2string("carid:",carid,"\tposx: ",x,"\tposy: ",y));
                if(magent.find(carid) == magent.end()){
                    magent[carid] = shared_ptr<Agent>(new Agent(carid, linkid,pathid));
					mslink[linkid]->inflow++;
					mslink[linkid]->poolnum++;
                }
                else{
                    if(magent[carid]->linkid != linkid){
                        //换道了
                        int pre_linkid = magent[carid]->linkid;
                        mslink[pre_linkid]->outflow++;
                        mslink[pre_linkid]->poolnum--;

                        mslink[linkid]->inflow++;
                        mslink[linkid]->poolnum++;

                        magent[carid]->linkid = linkid;
                    } 
                }
				cur_inscene.insert(carid);
            }

			//计算离开的agent
			for(auto carid : pre_inscene){
				if(cur_inscene.find(carid) == cur_inscene.end())
				{
					int pre_linkid = magent[carid]->linkid;
					mslink[pre_linkid]->outflow++;
					mslink[pre_linkid]->poolnum--;
				}	
			}

			pre_inscene.swap(cur_inscene);

            if(frame % interval == 0){
                //write to file
				//LOG_TRACE(my2string("frame:",frame, " num:" ,num));
                ofstream ofile;
                string outfile = outpath + "/sample.txt";
                ofile.open(outfile.c_str(),std::ios::app);
                ofile << frame << endl;
                for(auto slink : mslink){
                   ofile << slink.first << " " << slink.second->inflow << " " << slink.second->outflow
                        << " " << slink.second->poolnum << endl;
					slink.second->inflow = 0;
					slink.second->outflow = 0;
                }
                ofile.close();
            }
		}

		
		if(lastfile && frame % interval != 0) //最后一段不满足一个采样间隔
		{
			frame = interval * (frame/interval + 1);
			ofstream ofile;
			string outfile = outpath + "/sample.txt";
			ofile.open(outfile.c_str(),std::ios::app);
			ofile << frame << endl;
			for(auto slink : mslink){
				ofile << slink.first << " " << slink.second->inflow << " " << slink.second->outflow
					<< " " << slink.second->poolnum << endl;
			}
			ofile.close();
		}

	}catch(...){
		LOG_FATAL("can't read file content!!!");
	}
}

void PProcess::sampleByLink(const string& path,vector<int> link_ids, bool lastfile){

	try{
		fstream fin(path.c_str(),std::ifstream::in);
		string line;
		set<int> pre_inscene;
		int frame,num;
		while(std::getline(fin,line)){
			istringstream is(line);
			is >> frame >> num;

            int carid,type,linkid,pathid;
            double x,y,zh;
			set<int> cur_inscene;
			for(int i = 0; i < num; ++i){
				std::getline(fin,line);
                istringstream is(line);
                is >> carid >> x >> y >> type >> linkid >> zh;
                //LOG_TRACE(my2string("carid:",carid,"\tposx: ",x,"\tposy: ",y));
                if(magent.find(carid) == magent.end()){
                    magent[carid] = shared_ptr<Agent>(new Agent(carid, linkid));
					mslink[linkid]->inflow++;

                    if(zh < mslink[linkid]->pool_zh || fabs(zh - mslink[linkid]->pool_zh) < 1e-15 )   mslink[linkid]->poolnum++; //如果在pool中，则poolnum++
                    else if(zh > mslink[linkid]->buffer_zh)  mslink[linkid]->buffernum++; //如果在buffer中，则buffernum++;


                    mslink[linkid]->sum_zh += (zh - 0.0F);
                    mslink[linkid]->sum_frame++;
                }
                else{
                    if(magent[carid]->linkid != linkid){
                        //previous link
                        int pre_linkid = magent[carid]->linkid;
                        mslink[pre_linkid]->outflow++;

                        if(magent[carid]->zh < mslink[pre_linkid]->pool_zh || fabs(magent[carid]->zh - mslink[pre_linkid]->pool_zh) < 1e-15 ) {   
                            mslink[pre_linkid]->poolnum--; //如果之前在Pool中
                        }
                        else if(magent[carid]->zh > mslink[pre_linkid]->buffer_zh)   mslink[pre_linkid]->buffernum--; //如果之前在buffer中

                        double pre_delta_zh = mslink[pre_linkid]->length - magent[carid]->zh;
                        double cur_delta_zh = zh;

                        double pre_ratio = pre_delta_zh / (pre_delta_zh + zh);

                        mslink[pre_linkid]->sum_frame+= pre_ratio; //通过前后两端的时间应该按比例分配当前的frame,比如0.2,0.8
                        mslink[pre_linkid]->sum_zh += (pre_delta_zh); //累加增量的里程

                        //current link
                        mslink[linkid]->inflow++;

                        if(zh < mslink[linkid]->pool_zh || fabs(zh - mslink[linkid]->pool_zh) < 1e-15 )   mslink[linkid]->poolnum++; //如果现在在pool中
                        else if(zh > mslink[linkid]->buffer_zh)  mslink[linkid]->buffernum++; //如果现在在buffer中

                        //mslink[linkid]->poolnum++;
                        mslink[linkid]->sum_frame += (1-pre_ratio);
                        mslink[linkid]->sum_zh += (zh - 0.0F);

                        magent[carid]->linkid = linkid;
                    } 
                    else{ //still on current link

                        if( (magent[carid]->zh < mslink[linkid]->pool_zh || fabs(magent[carid]->zh - mslink[linkid]->pool_zh) < 1e-15)
                                && (zh > mslink[linkid]->buffer_zh)) //之前在pool,现在在buffer中
                        {
                            mslink[linkid]->poolnum--;
                            mslink[linkid]->buffernum++;
                        }
                        else if( (zh < mslink[linkid]->pool_zh || fabs(zh - mslink[linkid]->pool_zh) < 1e-15) 
                                && (magent[carid]->zh > mslink[linkid]->buffer_zh)) //现在在pool,之前在buffer中(很诡异)
                        {
                            mslink[linkid]->poolnum++;
                            mslink[linkid]->buffernum--;
                            cout << "carid:" << carid << ",link_id:" << linkid << endl;
                        }

                        mslink[linkid]->sum_frame++;
                        mslink[linkid]->sum_zh += (zh - magent[carid]->zh);
                    }
                }

                magent[carid]->zh = zh; //更新里程信息
				cur_inscene.insert(carid);
            }
			//计算离开的agent
			for(auto carid : pre_inscene){
				if(cur_inscene.find(carid) == cur_inscene.end())
				{
					int pre_linkid = magent[carid]->linkid;
					mslink[pre_linkid]->outflow++;

                    if(magent[carid]->zh < mslink[pre_linkid]->pool_zh || fabs(magent[carid]->zh - mslink[pre_linkid]->pool_zh) < 1e-15) mslink[pre_linkid]->poolnum--;//如果之前在Pool中
                    else if(magent[carid]->zh > mslink[pre_linkid]->buffer_zh)   mslink[pre_linkid]->buffernum--; //如果之前在buffer中

                    mslink[pre_linkid]->sum_frame ++; //这里粗略统计
                    mslink[pre_linkid]->sum_zh += (mslink[pre_linkid]->length - magent[carid]->zh);

				}	
			}
			pre_inscene.swap(cur_inscene);

            if(frame % interval == 0){
                //write to file
				//LOG_TRACE(my2string("frame:",frame, " num:" ,num));
				for(auto link_id : link_ids){
					ofstream ofile;
					string outfile = outpath + "/" + std::to_string(link_id)+"_link_sample.txt";
					ofile.open(outfile.c_str(),std::ios::app);
					auto slink = mslink[link_id];
					//ofile <<  frame << " " << slink->inflow << " " << slink->outflow << " " << slink->poolnum << endl;
                    ofile << frame;
                    ofile << "\t" << slink->poolnum << "\t" << slink->buffernum
                          << "\t" << slink->inflow << "\t"  << slink->outflow
                          << "\t" << slink->avg_speed << endl;
					ofile.close();
                    //重置统计量
					slink->inflow = 0;
					slink->outflow = 0;
                    slink->sum_frame = 0;
                    slink->sum_zh = 0;
                    slink->avg_speed = 0;
				}
            }
		}

		if(lastfile && frame % interval != 0) //最后一段不满足一个采样间隔
		{
			frame = interval * (frame/interval + 1);
            //计算平均速度
            for(auto mlink : mslink){
                    if(mlink.second->sum_frame > 0.0F)
                        mlink.second->avg_speed = mlink.second->sum_zh / (mlink.second->sum_frame * 0.1);
            }

			for(auto link_id : link_ids){
				ofstream ofile;
				string outfile = outpath + "/" + std::to_string(link_id)+"_link_sample.txt";
				ofile.open(outfile.c_str(),std::ios::app);
				auto slink = mslink[link_id];
                ofile << frame;
                ofile << "\t" << slink->poolnum << "\t" << slink->buffernum
                      << "\t" << slink->inflow << "\t"  << slink->outflow
                      << "\t" << slink->avg_speed << endl;
				ofile.close();

				slink->inflow = 0;
				slink->outflow = 0;
                slink->sum_frame = 0;
                slink->sum_zh = 0;
                slink->avg_speed = 0;
			}

		}

	}catch(...){
		LOG_FATAL("can't read file content!!!");
	}
}

void PProcess::sampleByNode(const string& path,vector<int> node_ids, bool lastfile){

    //addHeader(node_ids);
    addCommonHeader(node_ids);
	try{
		fstream fin(path.c_str(),std::ifstream::in);
		string line;
		set<int> pre_inscene;
		int frame,num;
		while(std::getline(fin,line)){
			istringstream is(line);
			is >> frame >> num;

            int carid,type,linkid,pathid;
            double x,y,zh;
			set<int> cur_inscene;
			for(int i = 0; i < num; ++i){
				std::getline(fin,line);
                istringstream is(line);
                is >> carid >> x >> y >> type >> linkid >> zh;
                //LOG_TRACE(my2string("carid:",carid,"\tposx: ",x,"\tposy: ",y));
                if(magent.find(carid) == magent.end()){
                    magent[carid] = shared_ptr<Agent>(new Agent(carid, linkid));
					mslink[linkid]->inflow++;

                    if(zh < mslink[linkid]->pool_zh || fabs(zh - mslink[linkid]->pool_zh) < 1e-15 )   mslink[linkid]->poolnum++; //如果在pool中，则poolnum++
                    else if(zh > mslink[linkid]->buffer_zh)  mslink[linkid]->buffernum++; //如果在buffer中，则buffernum++;


                    mslink[linkid]->sum_zh += (zh - 0.0F);
                    mslink[linkid]->sum_frame++;
                }
                else{
                    if(magent[carid]->linkid != linkid){
                        //previous link
                        int pre_linkid = magent[carid]->linkid;
                        mslink[pre_linkid]->outflow++;

                        if(magent[carid]->zh < mslink[pre_linkid]->pool_zh || fabs(magent[carid]->zh - mslink[pre_linkid]->pool_zh) < 1e-15 ) {   
                            mslink[pre_linkid]->poolnum--; //如果之前在Pool中
                        }
                        else if(magent[carid]->zh > mslink[pre_linkid]->buffer_zh)   mslink[pre_linkid]->buffernum--; //如果之前在buffer中

                        double pre_delta_zh = mslink[pre_linkid]->length - magent[carid]->zh;
                        double cur_delta_zh = zh;

                        double pre_ratio = pre_delta_zh / (pre_delta_zh + zh);

                        mslink[pre_linkid]->sum_frame+= pre_ratio; //通过前后两端的时间应该按比例分配当前的frame,比如0.2,0.8
                        mslink[pre_linkid]->sum_zh += (pre_delta_zh); //累加增量的里程

                        //current link
                        mslink[linkid]->inflow++;

                        if(zh < mslink[linkid]->pool_zh || fabs(zh - mslink[linkid]->pool_zh) < 1e-15 )   mslink[linkid]->poolnum++; //如果现在在pool中
                        else if(zh > mslink[linkid]->buffer_zh)  mslink[linkid]->buffernum++; //如果现在在buffer中

                        //mslink[linkid]->poolnum++;
                        mslink[linkid]->sum_frame += (1-pre_ratio);
                        mslink[linkid]->sum_zh += (zh - 0.0F);

                        magent[carid]->linkid = linkid;
                    } 
                    else{ //still on current link
                        if( (magent[carid]->zh < mslink[linkid]->pool_zh || fabs(magent[carid]->zh - mslink[linkid]->pool_zh) < 1e-15)
                                && (zh > mslink[linkid]->buffer_zh)) //之前在pool,现在在buffer中
                        {
                            mslink[linkid]->poolnum--;
                            mslink[linkid]->buffernum++;
                        }
                        else if( (zh < mslink[linkid]->pool_zh || fabs(zh - mslink[linkid]->pool_zh) < 1e-15) 
                                && (magent[carid]->zh > mslink[linkid]->buffer_zh)) //现在在pool,之前在buffer中(很诡异)
                        {
                            mslink[linkid]->poolnum++;
                            mslink[linkid]->buffernum--;
                            cout << "carid:" << carid << ",link_id:" << linkid << endl;
                        }


                        mslink[linkid]->sum_frame++;
                        mslink[linkid]->sum_zh += (zh - magent[carid]->zh);
                    }
                }

                magent[carid]->zh = zh; //更新里程信息
				cur_inscene.insert(carid);
            }
			//计算离开的agent
			for(auto carid : pre_inscene){
				if(cur_inscene.find(carid) == cur_inscene.end())
				{
					int pre_linkid = magent[carid]->linkid;
					mslink[pre_linkid]->outflow++;

                    if(magent[carid]->zh < mslink[pre_linkid]->pool_zh || fabs(magent[carid]->zh - mslink[pre_linkid]->pool_zh) < 1e-15) mslink[pre_linkid]->poolnum--;//如果之前在Pool中
                    else if(magent[carid]->zh > mslink[pre_linkid]->buffer_zh)   mslink[pre_linkid]->buffernum--; //如果之前在buffer中

                    mslink[pre_linkid]->sum_frame ++; //这里粗略统计
                    mslink[pre_linkid]->sum_zh += (mslink[pre_linkid]->length - magent[carid]->zh);

				}	
			}
			pre_inscene.swap(cur_inscene);

			//根据node的前后link进行采样
			//格式
			//汇入的link数，每个的poolnum、outflow，下游的link的inflow，poolnum
            if(frame % interval == 0){

                //计算link的平均速度
                for(auto mlink : mslink){
                    if(mlink.second->sum_frame > 0.0F)
                        mlink.second->avg_speed = mlink.second->sum_zh / (mlink.second->sum_frame * 0.1);
                        //if(mlink.second->avg_speed > 40)
                        //    LOG_WARNING(my2string("frame:",frame,"\tlink :", mlink.first , "\t " ,mlink.second->sum_zh, "\t " , mlink.second->sum_frame, "\tspeed: ",
                        //               mlink.second->avg_speed));
                }

				for(auto node_id : node_ids){
					ofstream ofile;
					string outfile = outpath + "/" + std::to_string(node_id) + "_node_sample.txt";
					ofile.open(outfile.c_str(),std::ios::app);

					ofile << frame;
					for(auto link_id : nodes[node_id]->flinks){
						auto slink = mslink[link_id];
						ofile << "\t" << slink->poolnum << "\t" << slink->buffernum
                              << "\t" << slink->inflow << "\t"  << slink->outflow
                              << "\t" << slink->avg_speed;
					}

					for(auto link_id : nodes[node_id]->tlinks){
						auto slink = mslink[link_id];
						ofile << "\t" << slink->poolnum << "\t" << slink->buffernum
                              << "\t" << slink->inflow << "\t" <<  slink->outflow
                              << "\t" << slink->avg_speed;
					}

					ofile << endl;
					ofile.flush();
					ofile.close();

				}
                //重置link的统计量
                for(auto mlink : mslink){
                    mlink.second->inflow = 0;
                    mlink.second->outflow = 0;
                    mlink.second->sum_frame = 0;
                    mlink.second->sum_zh = 0;
                    mlink.second->avg_speed = 0;
                }
            }
		}

		
		if(lastfile && frame % interval != 0) //最后一段不满足一个采样间隔
		{
			frame = interval * (frame/interval + 1);

            //计算平均速度
            for(auto mlink : mslink){
                    if(mlink.second->sum_frame > 0.0F)
                        mlink.second->avg_speed = mlink.second->sum_zh / (mlink.second->sum_frame * 0.1);
            }

			for(auto node_id : node_ids){
				ofstream ofile;
				string outfile = outpath + "/" + std::to_string(node_id) + "_node_sample.txt";
				ofile.open(outfile.c_str(),std::ios::app);

				ofile << frame;
				for(auto link_id : nodes[node_id]->flinks){
					auto slink = mslink[link_id];
                    ofile << "\t" << slink->poolnum << "\t" << slink->buffernum
                          << "\t" << slink->inflow << "\t"  << slink->outflow
                          << "\t" << slink->avg_speed;
				}

				for(auto link_id : nodes[node_id]->tlinks){
					auto slink = mslink[link_id];
                    ofile << "\t" << slink->poolnum << "\t" << slink->buffernum
                          << "\t" << slink->inflow << "\t" <<  slink->outflow
                          << "\t" << slink->avg_speed;
				}

				ofile << endl;
				ofile.flush();
				ofile.close();
			}
		}

	}catch(...){
		LOG_FATAL("can't read file content!!!");
	}
}

void PProcess::init(){
    //初始化填充Link
    mslink.clear();
    magent.clear();

    for(auto path: paths){
        for(auto linkid : path){
            if(mslink.find(linkid) == mslink.end()){
                mslink[linkid] = shared_ptr<Link>(new Link());
                mslink[linkid]->length = links[linkid]->length;
                mslink[linkid]->pool_zh = links[linkid]->pool_zh;
                mslink[linkid]->buffer_zh= links[linkid]->buffer_zh;
            }
        }
    }
}

void PProcess::doSampleByTime(){
	vector<string> filelist = getFilelist(inpath,pattern);
	int filenum = 1;
	for(auto filename : filelist){
		LOG_TRACE(my2string("read file: ",filename));
		sampleByTime(filename,filenum == filelist.size());
		filenum++;
	}
}

void PProcess::doSampleByLink(vector<int> linkids){

    init();

	vector<string> filelist = getFilelist(inpath,pattern);
	int filenum = 1;
	for(auto filename : filelist){
		LOG_TRACE(my2string("read file: ",filename));
		sampleByLink(filename,linkids,filenum == filelist.size());
		filenum++;
	}
}

void PProcess::doSampleByNode(vector<int> nodeids){

    init();

	vector<string> filelist = getFilelist(inpath,pattern);
	int filenum = 1;
	for(auto filename : filelist){
		LOG_TRACE(my2string("read file: ",filename));
		sampleByNode(filename,nodeids,filenum ==  filelist.size());
		filenum++;
	}
}

void PProcess::clean(){
	if(bf::exists(outpath)){
		uint32_t delete_num = bf::remove_all(outpath);
		LOG_DEBUG(my2string("Remove ", delete_num, " Sample File."));	
	}
	bf::create_directory(outpath);
}

//采样哪个删除哪个
void PProcess::clean(vector<int> link_ids, vector<int>node_ids)
{
    for(auto link_id: link_ids){
        string outfile = outpath + "/" + std::to_string(link_id) + "_link_sample.txt";
        if(bf::exists(outfile)){
            uint32_t delete_num = bf::remove(outfile);
            LOG_DEBUG(my2string("Remove ", outfile));   
        }
    }

    for(auto node_id : node_ids){
        string outfile = outpath + "/" + std::to_string(node_id) + "_node_sample.txt";
        if(bf::exists(outfile)){
            uint32_t delete_num = bf::remove(outfile);
            LOG_DEBUG(my2string("Remove ", outfile));   
        }
    }
}

void PProcess::addHeader(const vector<int>& node_ids){
    for(auto node_id : node_ids){
        ofstream ofile;
        string outfile = outpath + "/" + std::to_string(node_id) + "_node_sample.txt";

        if(!bf::exists(outfile)){
            ofile.open(outfile.c_str(),std::ios::app);
            ofile << "frame";
            for(auto link_id : nodes[node_id]->flinks){
                auto slink = mslink[link_id];
                auto prefix = std::to_string(link_id) + "_";
                ofile << "\t" << prefix + "poolnum" << "\t" << prefix + "buffernum"
                    << "\t" << prefix + "inflow" << "\t"  << prefix + "outflow"
                    << "\t" << prefix + "speed";
            }

            for(auto link_id : nodes[node_id]->tlinks){
                auto slink = mslink[link_id];
                auto prefix= std::to_string(link_id) + "_";
                ofile << "\t" << prefix + "poolnum" << "\t" << prefix + "buffernum"
                    << "\t" << prefix + "inflow" << "\t"  << prefix + "outflow"
                    << "\t" << prefix + "speed";
            }
            ofile << endl;
            ofile.flush();
            ofile.close();
        } 
    }
}

//通用的header，只适用于单条路线（有并道的不行)
void PProcess::addCommonHeader(const vector<int>& node_ids){
    for(auto node_id : node_ids){
        ofstream ofile;
        string outfile = outpath + "/" + std::to_string(node_id) + "_node_sample.txt";

        if(!bf::exists(outfile)){
            ofile.open(outfile.c_str(),std::ios::app);

            ofile << "frame";
            if(nodes[node_id]->flinks.size())
                ofile << "\tpre_poolnum\tpre_buffernum\tpre_inflow\tpre_outflow\tpre_speed";
            if(nodes[node_id]->tlinks.size())
                ofile << "\tcur_poolnum\tcur_buffernum\tcur_inflow\tcur_outflow\tcur_speed";

            ofile << endl;
            ofile.flush();
            ofile.close();
        } 
    }
}
