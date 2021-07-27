// Guilherme Fernandes Gonçalves Silva             NUSP 10297272
// Rodrigo Estevam de Paula                        NUSP 10773843

#include <cekeikon.h>

int main(){  
    Mat_<GRY> ax; le(ax,"aprendizagem/janei.pgm");  
    Mat_<GRY> ay; le(ay,"aprendizagem/janei-1.pgm");  
    Mat_<GRY> qx; le(qx,"aprendizagem/julho.pgm");
    if(ax.size()!=ay.size()) erro("Erro dimensao");  
    Mat_<GRY> qp(qx.rows,qx.cols);
    //Cria as estruturas de dados para alimentar OpenCV  
    Mat_<FLT> features(ax.rows*ax.cols,9);  
    Mat_<FLT> saidas(ax.rows*ax.cols,1);int i=0;
    for(int l=1; l<ax.rows-1; l++)
        for(int c=1; c<ax.cols-1; c++){      
            features(i,0)=ax(l-1,c-1)/255.0;      
            features(i,1)=ax(l-1,c)/255.0;      
            features(i,2)=ax(l,c+1)/255.0;
            features(i,3)=ax(l,c-1)/255.0;
            features(i,4)=ax(l,c)/255.0;      
            features(i,5)=ax(l+1,c)/255.0;
            features(i,6)=ax(l-1,c+1)/255.0;
            features(i,7)=ax(l+1,c-1)/255.0;
            features(i,8)=ax(l+1,c+1)/255.0;
            saidas(i)=ay(l,c)/255.0;      
            i=i+1;
        }  
    flann::Index ind(features,flann::KDTreeIndexParams(4));

    // Aqui, as 4 arvores estao criadas  
    Mat_<FLT> query(1,9);  
    vector<int> indices(9);  
    vector<FLT> dists(9);
    
    for(int l=1; l<qp.rows-1; l++)
        for(int c=1; c<qp.cols-1; c++){      
            query(0)=qx(l-1,c-1)/255.0;      
            query(1)=qx(l-1,c)/255.0;      
            query(2)=qx(l,c+1)/255.0;
            query(3)=qx(l,c-1)/255.0;
            query(4)=qx(l,c)/255.0;      
            query(5)=qx(l+1,c)/255.0;
            query(6)=qx(l-1,c+1)/255.0;
            query(7)=qx(l+1,c-1)/255.0;
            query(8)=qx(l+1,c+1)/255.0;;      
            ind.knnSearch(query,indices,dists,1,flann::SearchParams(0));   
            qp(l,c)=255*saidas(indices[0]);
        }  
    imp(qp,"aprendizagem/julho-p1.pgm");
    
    Mat_<GRY> mqp;
    medianBlur(qp, mqp, 9);
    imp(mqp,"aprendizagem/julho-fp1.pgm");

    Mat_<COR> cy; le(cy,"aprendizagem/julho.pgm");
    for(int l=0; l<mqp.rows; l++)
        for(int c=0; c<mqp.cols; c++){
            if(mqp(l,c) == 0){
                cy(l,c)[2] = 255;
            }
        }
    imp(cy,"aprendizagem/julho-c1.png");


}

