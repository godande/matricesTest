#include <iostream>
#include <vector>
template <class T>
class Matrix{
    public:

    // get,set for width
        
        void setWidth(int width){
            this->x = width;
        }
        int getWidth(){
            return this->x;
        }

    //get,set for height

        void setHeight(int height){
            this->y = height;
        }
        int getHeight(){
            return this->y;
        }

    std::vector<std::vector<T>> values;
    
    // some constructors

    Matrix(std::vector<std::vector<T>> inits){
        this->values = inits;
        setHeight(inits.size());
        setWidth(inits[0].size());
    }
    Matrix(int side,std::string type){
        this->values = std::vector<std::vector<T>>(side,std::vector<T>(side,0));
        if(type == "identity"){ // initialize identity matrix;
            for(int i = 0; i < side; i++){
                this->values[i][i] = 1;
            }
        }
        setWidth(side);
        setHeight(side);
    }
    Matrix(int width, int height){
        this->values = std::vector<std::vector<T>>(height,std::vector<T>(width,0));
    }
    Matrix(){
        setWidth(1);
        setHeight(1);
        this->values = std::vector<std::vector<T>> {{1}};
    }
    // matrix operations

    static Matrix multiplication(Matrix a, Matrix b){
        
        std::vector<std::vector<T>>  result(a.getHeight(),std::vector<T>(b.getWidth(),0));
        
        for(int i = 0; i < a.getHeight(); ++i){
            for(int j = 0; j < b.getWidth(); ++j){
                for(int k = 0; k < a.getWidth(); ++k){
                    result[i][j] += a.values[i][k] * b.values[k][j];
                }
            }
        }
        
        return Matrix<T>(result);
    }
    static Matrix addition(Matrix a, Matrix b){
        std::vector<std::vector<T>>  result(a.getHeight(),std::vector<T>(a.getWidth(),0));
        if(a.getHeight() ^ b.getHeight() + a.getWidth() * b.getWidth() != 0){
            std::cout << "a size != b size";
            return Matrix<T>(result);
        }else{
            for(int i = 0 ; i < a.getHeight(); i++){
                for(int j = 0; j < b.getHeight(); j++){
                    result[i][j] = a.values[i][j] + b.values[i][j];
                }
            }
            return Matrix<T>(result);
        }
    }

    static Matrix substracion(Matrix a, Matrix b){
        std::vector<std::vector<T>>  result(a.getHeight(),std::vector<T>(a.getWidth(),0));
        if(a.getHeight() ^ b.getHeight + a.getWidth() * b.getWidth != 0){
            std::cout << "a size != b size";
            return Matrix<T>(result);
        }else{
            for(int i = 0 ; i < a.getHeight(); i++){
                for(int j = 0; j < b.getHeight(); j++){
                    result[i][j] = a.values[i][j] - b.values[i][j];
                }
            }
            return Matrix<T>(result);
        }
    }

    static Matrix transpose(Matrix a){
        std::vector<std::vector<T>>  result(a.getWidth(),std::vector<T>(a.getHeight(),0));
        
        for(int i = 0; i < a.getHeight(); ++i){
            for(int j = 0; j < a.getWidth(); ++j){
                result[j][i] = a.values[i][j];
            }
        }
        
        return Matrix<T>(result);
    }
    static Matrix pow(Matrix a, int pow){
        Matrix<T> temp = a;
        Matrix<T> result(Matrix<double>(a.values));
        while(pow){
                if(pow & 1)
                    result = Matrix<T>::multiplication(result,temp);
                temp = Matrix<T>::multiplication(temp,temp);
                pow >>= 1;
        }
        
        return result;
    }

    static T determinant(Matrix a){
        T temp = 0;
        int power = 1;
        if(a.getHeight() == 1){
            temp = a.values[0][0];
        }
        else if(a.getHeight() == 2){
            temp = a.values[0][0] * a.values[1][1] - a.values[1][0] * a.values[0][1];
            for(int i = 0; i < a.getHeight();i++)
            {
                for(int j = 0; j < a.getHeight();j++){
                    std::cout << a.values[i][j] << " ";
                }
                std::cout << "\n";
            }
            std::cout << "\n\n\n";
        }
        else{
            for(int i = 0; i < a.getHeight(); i++){
                temp += power * a.values[0][i] * determinant(buildMatrix(a,i,0));
                power = -power; 
            }
        }
        return temp;
    }
    // destructor

    ~Matrix(){
        for(auto arr : this->values){
            arr.clear();
            arr.shrink_to_fit();
        }
        this->values.clear();
        this->values.shrink_to_fit();
    }

    //some fields 

    private:
        int x,y;
        static Matrix buildMatrix(Matrix a,int x, int y){
            std::vector<std::vector<T>>  result(a.getWidth()-1,std::vector<T>(a.getHeight()-1,0));
            int di,dj;
            di=0;
            for(int i = 0; i < a.getHeight()-1; i++){
                if(i == y){
                    di = 1;
                }
                dj = 0;
                for(int j = 0; j < a.getWidth()-1; j++){
                    if(j == x){
                        dj = 1;
                    }
                    result[i][j] = a.values[i+di][j+dj];
                }
                
            }
            
            
            return Matrix<T>(result);
        }
};


int main(){
    std::vector<double> a{1.0,2.0,3.0};
    std::vector<double> b{4.0,5.0,6.0};
    std::vector<std::vector<double>> initialize{a,b};
    std::vector<std::vector<double>> initializeSwapped{b,a};
    std::vector<std::vector<double>> initializePow{std::vector<double>{4,5,6},std::vector<double>{1,2,3},std::vector<double>{4,5,6}};
    Matrix<double> urmom(initialize);
    Matrix<double> urmom2(initializeSwapped);
    Matrix<double> powed(initializePow);
    std::cout << "Height:" <<  urmom.getHeight() << "\n";
    std::cout << "Width:" << urmom.getWidth() << "\n";
    Matrix<double> trans = Matrix<double>::transpose(urmom);
    for(int i = 0; i < trans.getHeight(); i++){
        for(int j = 0; j < trans.getWidth(); j++)
            std::cout << trans.values[i][j] << " ";
        std::cout << "\n";
    }
    std::cout << "\n";
    Matrix<double> multed = Matrix<double>::multiplication(urmom,trans);
    for(int i = 0; i < multed.getHeight(); i++){
         for(int j = 0; j < multed.getWidth(); j++)
             std::cout << multed.values[i][j] << " ";
        std::cout << "\n";
    }
    std::cout << "\n";
    Matrix<double> powder = Matrix<double>::pow(powed,2);
    for(int i = 0; i < powder.getHeight(); i++){
         for(int j = 0; j < powder.getWidth(); j++)
             std::cout << powder.values[i][j] << " ";
        std::cout << "\n";
    }
    std::cout << Matrix<double>::determinant(powed) << "\n";
}