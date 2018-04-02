import networkx as nx
import matplotlib.pyplot as plt
import xml.dom.minidom as dm
import setting as st
import os

def loadEdges(node_file):

    edges = []

    dom = dm.parse(node_file)
    root = dom.documentElement

    start_idx = 0
    nodes = root.getElementsByTagName("node")
    for node in nodes:
        if node.hasAttribute("id"):
            flinks = node.getElementsByTagName("flinks")[0]
            tlinks = node.getElementsByTagName("tlinks")[0]

            flinks_str = []
            tlinks_str = []

            if len(flinks.childNodes) == 0:
                flinks_str = [start_idx]
                start_idx = start_idx + 1
            else:
                flinks_str = flinks.childNodes[0].data.split()

            if len(tlinks.childNodes) == 0:
                #tlinks_str = [10000]
                tlinks_str = [node.getAttribute("id")]
            else:
                tlinks_str = tlinks.childNodes[0].data.split()

            for fid in flinks_str:
                for tid in tlinks_str:
                    edges.append((fid,tid))



    print(edges)
    return edges



def showNetwork(node_file):

    edges = loadEdges(node_file)

    G = nx.DiGraph()
    G.add_edges_from(edges)


    # Need to create a layout when doing
    # separate calls to draw nodes and edges
    #pos = nx.spring_layout(G)
    #pos = nx.shell_layout(G)
    #pos = nx.circular_layout(G)
    pos = nx.spectral_layout(G)
    nx.draw_networkx_nodes(G, pos, cmap=plt.get_cmap('jet'),node_size=500)
    nx.draw_networkx_labels(G, pos, font_size = 8)
    nx.draw_networkx_edges(G, pos, edgelist=edges, edge_color='black', arrows=True)
    #plt.show()
    plt.savefig(fname = 'fig/network.png', format = 'png',dpi = 500)


#loadNetwork("../data/data_qs/network/node.xml")
#showNetwork("../data/data_qs/network/node.xml")
showNetwork(os.path.join(st.data_root,"network/node.xml"))
