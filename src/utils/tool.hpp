#ifndef __TOOL_HPP_
#define __TOOL_HPP_

inline void print(std::ostringstream &os){
	return;
}

template<typename T, typename ...Args>
inline void print(std::ostringstream & os , T head, Args... rest){
	os << head;	
	if(sizeof...(rest) == 0) return;
	print(os, rest...);
}

template<typename ...Args>
inline std::string my2string(Args... rest){
	std::ostringstream os;
	print(os,rest...);
	return std::move(os.str());
}

#endif