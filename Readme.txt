This is an example of DNF to compute the network flow matrix by using two constructed networks
In this example, 7 files were used.
To run this example, you only need to run these file numbered by 1,2,3 in order 

File description
1.DNF_hsc.cpp
compute the network flow matrix of HSC cell network
2.DNF_mpp.cpp
compute the network flow matrix of MPP cell network
3.DNF_compute.r
compute and rank genes by DNF based on above two matrices
HSC_edgelist.txt
The edgelist form of HSC cell network, where col1 and col2 corresponding to genes, col3 corresponding to abs(SCC), col4 was not used here.
MPP_edgelist.txt
The edgelist form of MPP cell network, where col1 and col2 corresponding to genes, col3 corresponding to abs(SCC), col4 was not used here.
HSC_genelist.txt
Mapping genes from numbers (used in cpp files) to characters (gene symbols)
MPP_genelist.txt
Mapping genes from numbers (used in cpp files) to characters (gene symbols)
