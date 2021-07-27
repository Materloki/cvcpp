// Guilherme Fernandes Gonçalves Silva             NUSP 10297272
// Rodrigo Estevam de Paula                        NUSP 10773843
//Erros=      2.36%
//Tempo de treinamento: 11.980666
//  Tempo de predicao: 2.050990
#include <cekeikon.h>
int main(){  
    MNIST mnist(12,true,true);  mnist.le("/home/materloki/cekeikon5/tiny_dnn/data");  
    Mat_<FLT> new_ax(3*mnist.na, 144);
    Mat_<FLT> new_ay(3*mnist.na, 1);

    for(int i =0; i < mnist.na; i++)
    {
        for(int j = 0; j<144; j++)
        {
            new_ax(3*i,j) = mnist.ax(i,j);
            if(j!=143){
                new_ax(3*i+1,j) = 1;
            }
            else{
                new_ax(3*i+1,j) = mnist.ax(i,j+1);
            }
            if(j!=0){
                new_ax(3*i+2,j) = 1;
            }
            else{
                new_ax(3*i+2,j) = mnist.ax(i,j-1);
            }
        }
    }

    for(int i =0; i<mnist.na; i++)
    {
        for(int j=0; j <3; j++){
            new_ay(3*i+j,1) = mnist.ay(i,1);

        }
    }    
    
    TimePoint t1=timePoint();  
    flann::Index ind(new_ax,flann::KDTreeIndexParams(64));  
    TimePoint t2=timePoint();  
    vector<int> indices(1); 
    vector<float> dists(1);



    for(int l=0; l<mnist.qx.rows; l++){    
        ind.knnSearch(mnist.qx.row(l),indices,dists,1,flann::SearchParams(256));    
        mnist.qp(l)=new_ay(indices[0]);
    }  
        TimePoint t3=timePoint();
    printf("Erros=%10.2f%%\n",100.0*mnist.contaErros()/mnist.nq);  
    printf("Tempo de treinamento: %f\n",timeSpan(t1,t2));  
    printf("Tempo de predicao: %f\n",timeSpan(t2,t3));
}