
#include <math.h>
#include <time.h>
#include <stdio.h>

    SimpleMatrix<float> D;//declaring outside allows you to use up to the total 2GB available to any 32bit program
    SimpleMatrix<float> E;
    SimpleMatrix<float> F;


double Add1(double A)
{
    A=A+1;
    return A;
}
double MultAdd1(double A, double B){return (A*B+1);}

void TESTSimpleMatrix(void)
{
    clock_t startTime;
    double millisecondsPassed;


    /// Constructors
//    SimpleMatrix(int xsize, int ysize);//alows a vector to be used to specify the dimensions of the matrix
    SimpleMatrix<double> A(2, 3);
    cout<<"2x3"<<endl;
    A.displayinfo();
//    SimpleMatrix(void);
    SimpleMatrix<double> U;
    cout<<"1x1"<<endl;
    U.displayinfo();
//    SimpleMatrix(vector<int> dimensions);//alows a vector to be used to specify the dimensions of the matrix
    vector<int> SizingVector;
    SizingVector.push_back(5);
    SizingVector.push_back(6);
    SimpleMatrix<double> B(SizingVector);
    cout<<"5x6 vector"<<endl;
    B.displayinfo();
//    void resize(int xsize, int ysize);
    B.resize(3, 4);
    cout<<"3x4 resize down using ints"<<endl;
    B.displayinfo();
//    void resize(vector<int> dimensions);
    SizingVector[0]=3;
    SizingVector[1]=4;
    A.resize(SizingVector);
    cout<<"3x4 resize up using vector"<<endl;
    A.displayinfo();
//
    B(0, 3)=45;
    B.displayinfo();

    /// Dimensions
//    vector<int> dim(void);
    vector<int> DimReturn;
    DimReturn=B.dim();
    cout<<"Vector dim output "<<DimReturn[0]<<", "<<DimReturn[1]<<endl;
//    int xsize(void);
//    int ysize(void);
    cout<<"Int dim output "<<B.xsize()<<", "<<B.ysize()<<endl;
//    template <typename OtherType>
//    bool dimequal( SimpleMatrix<OtherType> Other);
    if (B.dimequal(A))
        cout<<"Dimensions compatible, as expected. Now resize"<<endl;

    A.resize(5, 4);
    if (!B.dimequal(A))
        cout<<"Too big in x works"<<endl;
    A.resize(2, 4);
    if (!B.dimequal(A))
        cout<<"Too small in x works"<<endl;
    A.resize(3, 5);
    if (!B.dimequal(A))
        cout<<"Too big in y works"<<endl;
    A.resize(3, 2);
    if (!B.dimequal(A))
        cout<<"Too small in y works"<<endl;

//    template <typename OtherType>
//    void StopIfDimensionsIncompatible(SimpleMatrix<OtherType> Other);
    //B.StopIfDimensionsIncompatible(A);
    //Works

//    // void StopIfDimensionsIncompatible( SimpleMatrix<OtherType> Other);
//    void setall(TemplateType SetValue);
    A.setall(55);
    A.displayinfo();

//    SimpleMatrix<TemplateType> transpose(void);
    A.resize(3, 4);
    for (int i=0; i<(3); i++)
        for (int j=0; j<(4); j++)
            A(i, j)=10*i+j;
    A.displayinfo();
    A.transpose();
    cout<<"Transpose of the above"<<endl;
    A.displayinfo();



    ///Getting values
//        TemplateType operator()(int i, int j)const{ return values[i][j];};
//
    cout<<"The number should say 23: "<<A(2, 3)<<endl;
    ///Setting Values
//        TemplateType & operator()(int i, int j){ return values[i][j];};
//  Tested above
//
    //Plus
//        template <typename OtherType>
//        SimpleMatrix<TemplateType> operator+(const SimpleMatrix<OtherType>& Other);
//        template <typename OtherType>
//        SimpleMatrix<TemplateType> operator+(const OtherType& Other);
    cout<<"A: "<<endl;
    A.displayinfo();

    cout<<"Testing int add"<<endl;
    int Two=2;
    B=A+Two;
    B.displayinfo();
    cout<<"Testing left int add"<<endl;
    B=Two+A;
    B.displayinfo();

    cout<<"Testing float add"<<endl;
    float TreefiddyF=3.5;
    B=A+TreefiddyF;
    B.displayinfo();

    cout<<"Testing double add"<<endl;
    double TreefiddyD=3.5;
    B=A+TreefiddyD;
    B.displayinfo();

    SimpleMatrix<double> C;
    cout<<"Testing matrix add"<<endl;
    C=A+B;
    C.displayinfo();

    //Minus
//        template <typename OtherType>
//        SimpleMatrix<TemplateType> operator-(const SimpleMatrix<OtherType>& Other);
//        template <typename OtherType>
//        SimpleMatrix<TemplateType> operator-(const OtherType& Other);
//        //Unary minus
//        SimpleMatrix<TemplateType> operator-(void);
    cout<<"A: "<<endl;
    A.displayinfo();

    cout<<"Testing int minus"<<endl;
    B=A-Two;
    B.displayinfo();
    cout<<"Testing left int minus"<<endl;
    B=Two-A;
    B.displayinfo();

    cout<<"Testing float minus"<<endl;
    B=A-TreefiddyF;
    B.displayinfo();

    cout<<"Testing double minus"<<endl;
    B=A-TreefiddyD;
    B.displayinfo();

    cout<<"Testing matrix minus"<<endl;
    C=A-B;
    C.displayinfo();

    cout<<"Testing unitary minus"<<endl;
    B=-A;
    B.displayinfo();

    //Times
//        template <typename OtherType>
//        SimpleMatrix<TemplateType> operator*(const SimpleMatrix<OtherType>& Other);
//        template <typename OtherType>
//        SimpleMatrix<TemplateType> operator*(const OtherType& Other);

    cout<<"A: "<<endl;
    A.displayinfo();

    cout<<"Testing int times"<<endl;
    B=A*Two;
    B.displayinfo();
    cout<<"Testing left int times"<<endl;
    B=Two*A;
    B.displayinfo();

    cout<<"Testing float times"<<endl;
    B=A*TreefiddyF;
    B.displayinfo();

    cout<<"Testing double times"<<endl;
    B=A*TreefiddyD;
    B.displayinfo();

    cout<<"Testing matrix times"<<endl;
    C=A*B;
    C.displayinfo();
    //Divide
//        template <typename OtherType>
//        SimpleMatrix<TemplateType> operator/(const SimpleMatrix<OtherType>& Other);
//        template <typename OtherType>
//        SimpleMatrix<TemplateType> operator/(const OtherType& Other);
//        template <typename OtherType>
//        SimpleMatrix<TemplateType> DivideByMatrix(const OtherType& Other);

    cout<<"A: "<<endl;
    A.displayinfo();

    cout<<"Testing int divide"<<endl;
    B=A/Two;
    B.displayinfo();
    cout<<"Testing left int divide"<<endl;
    B=Two/A;
    B.displayinfo();

    cout<<"Testing float divide"<<endl;
    B=A/TreefiddyF;
    B.displayinfo();

    cout<<"Testing double divide"<<endl;
    B=A/TreefiddyD;
    B.displayinfo();

    cout<<"Testing matrix divide"<<endl;
    C=A/B;
    C.displayinfo();


    //Modulus
//        template <typename OtherType>
//        SimpleMatrix<TemplateType> operator%(const SimpleMatrix<OtherType>& Other);
//        template <typename OtherType>
//        SimpleMatrix<TemplateType> operator%(const OtherType& Other);
//        template <typename OtherType>
//        SimpleMatrix<TemplateType> ModulusByMatrix(const OtherType& Other);
//

//    //Changes this matrix
//    void apply(TemplateType (*FunctionPointer)(TemplateType));
//    //returns a new matrix
//    template <typename ReturnTemplateType>
//    friend SimpleMatrix<ReturnTemplateType> apply(ReturnTemplateType (*FunctionPointer)(TemplateType), const SimpleMatrix<TemplateType> A);
//    //returns a new matrix, two input matrices
//    template <typename ReturnTemplateType>
//    friend SimpleMatrix<ReturnTemplateType> apply(ReturnTemplateType (*FunctionPointer)(TemplateType, TemplateType), const SimpleMatrix<TemplateType> A, const SimpleMatrix<TemplateType> B);




    cout<<"Applying add 1 to A"<<endl;
    A.apply(Add1);
    A.displayinfo();

    B=apply(Add1, A);
    B.displayinfo();

    C=apply(MultAdd1, A, B);
    C.displayinfo();



    cout<<"Testing the joining of matrices"<<endl;
    A.resize(5, 6);
    B.resize(4, 6);
    C=xjoin(A, B);
    C.displayinfo();

    //Testing that it looks right
    int Axsize, Aysize, Bxsize, Bysize;
    Axsize=3;
    Aysize=4;
    Bxsize=4;
    Bysize=4;
    A.resize(Axsize, Aysize);
    for (int i=0; i<Axsize; i++)
        for (int j=0; j<Aysize; j++)
            A(i, j)=3000+10*i+j;
    B.resize(Bxsize, Bysize);
    for (int i=0; i<Bxsize; i++)
        for (int j=0; j<Bysize; j++)
            B(i, j)=6000+10*i+j;

    C=xjoin(A, B);
    C.display();

    Axsize=3;
    Aysize=2;
    Bxsize=3;
    Bysize=5;
    A.resize(Axsize, Aysize);
    for (int i=0; i<Axsize; i++)
        for (int j=0; j<Aysize; j++)
            A(i, j)=3000+10*i+j;
    B.resize(Bxsize, Bysize);
    for (int i=0; i<Bxsize; i++)
        for (int j=0; j<Bysize; j++)
            B(i, j)=6000+10*i+j;


    C=yjoin(A, B);
    C.display();




    bool DoSpeedTest=false;
    if (DoSpeedTest)
    {
        cout<<"Starting speed run, check memory space"<<endl;

        int xdim=10000;
        int ydim=10000;
        D.resize(xdim, ydim);
        E.resize(xdim, ydim);

        int DSize=sizeof(D);
        cout<<"The size of a 10000x10000 vector is "<<DSize<<endl;

        for (int i=0; i<(xdim); i++)
            for (int j=0; j<(ydim); j++)
                D(i, j)=ydim*i+j;


        cout<<"Adding"<<endl;
        startTime=clock();
        E=D+2;
        millisecondsPassed = (clock() - startTime) / (CLOCKS_PER_SEC/1000);
        cout<<"Milliseconds: "<<millisecondsPassed<<endl;

        cout<<"Dividing"<<endl;
        startTime=clock();
        F=D/E;
        millisecondsPassed = (clock() - startTime) / (CLOCKS_PER_SEC/1000);
        cout<<"Milliseconds: "<<millisecondsPassed<<endl;

        cout<<"Dividing into preallocated space"<<endl;// is prealloacted becaur C is currently the right size
        F.setall(0.5);
        startTime=clock();
        F=D/E;
        millisecondsPassed = (clock() - startTime) / (CLOCKS_PER_SEC/1000);
        cout<<"Milliseconds: "<<millisecondsPassed<<endl;
    }







    //char buffer;
    //cin>>buffer;
}




