library(igraph)
working_dictionary = "D:/COML/Network flow/4_single_cell_rna_seq_datasets_comparison"
setwd(working_dictionary)



Norm = function(matrix)
{
  sum = rowSums(matrix)
  mat = apply(matrix,2,function(x) x/sum)
  return(mat)
}

KLD = function(shan1,shan2)
{
  result = rep(0,nrow(shan1))
  names(result) = rownames(shan1)
  for(i in rownames(shan1))
  {
    temp = 0;
    for(j in colnames(shan1))
    {
      if(i == j)
      {
        next
      }
      temp = temp + shan1[i,j]*log2(shan1[i,j]/shan2[i,j]) + shan2[i,j]*log2(shan2[i,j]/shan1[i,j])
    }
    result[i] = temp
  }     
  return(result)
}



data_fold = "GSE59114"
#读入网络流矩阵
shan1 = read.table(paste(data_fold,"HSC_result_network.txt",sep = "/"))
shan2 = read.table(paste(data_fold,"MPP_result_network.txt",sep = "/"))
anno1 = read.table(paste(data_fold,"HSC_genelist.txt",sep = "/"))
anno2 = read.table(paste(data_fold,"MPP_genelist.txt",sep = "/"))
rownames(shan1) = colnames(shan1) = anno1$V2
rownames(shan2) = colnames(shan2) = anno2$V2

#标准化
inter = intersect(colnames(shan1),colnames(shan2))
shan1 = shan1[inter,inter]
shan2 = shan2[inter,inter]
shan1 = Norm(shan1)
shan2 = Norm(shan2)
#计算KL散度
kld = KLD(shan1,shan2)

write.csv(kld,paste(data_fold,"DNF_result.csv",sep = "/"))