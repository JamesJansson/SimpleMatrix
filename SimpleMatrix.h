/// SimpleMatrix
// Developed by James Jansson
// This library is licensed under the Boost Software License 2003 (see end of file for terms).

///Description
// This library is essentially compiler candy, designed to reduce the size of matrix operations from several lines down to a single line.
// At this stage, all operations are done element-wise (that is, multiplication is element by element, not matrix multiplication as described in vector algebra).
// Please note that none of these functions have been security tested as they are intended for scientific computing.

// *** This library will likely require c++11 setting turned on in your compiler. ***

#include <vector>
using namespace std;



/// Class declarations
template <typename TemplateType>
class SimpleMatrix {
    vector<vector<TemplateType>> values;//Data is stored in the value array
    int xdimsize;
    int ydimsize;



    public:
    /// Constructors
    SimpleMatrix(int xsize, int ysize);//alows a vector to be used to specify the dimensions of the matrix
    SimpleMatrix(void);
    SimpleMatrix(vector<int> dimensions);//alows a vector to be used to specify the dimensions of the matrix
    void resize(int xsize, int ysize);
    void resize(vector<int> dimensions);

    /// Dimensions
    vector<int> dim(void);
    int xsize(void);
    int ysize(void);
    template <typename OtherType>
    bool dimequal( SimpleMatrix<OtherType> Other);
    template <typename OtherType>
    void stop_if_dim_not_equal(SimpleMatrix<OtherType> Other);
    void setall(TemplateType SetValue);
    void transpose(void);




    /// Overloading, pointer and template functions
    // Good tutorial on how this works: http://www.cprogramming.com/tutorial/operator_overloading.html
    // Index overloading
    // use () instead http://stackoverflow.com/questions/2533235/operator-c
    ///Getting values
        TemplateType operator()(int i, int j)const{ return values[i][j];};

    ///Setting Values
        TemplateType & operator()(int i, int j){ return values[i][j];};


    //Plus
        template <typename OtherType>
        SimpleMatrix<TemplateType> operator+(const SimpleMatrix<OtherType>& Other);
        template <typename OtherType>
        SimpleMatrix<TemplateType> operator+(const OtherType& Other);
    //Minus
        template <typename OtherType>
        SimpleMatrix<TemplateType> operator-(const SimpleMatrix<OtherType>& Other);
        template <typename OtherType>
        SimpleMatrix<TemplateType> operator-(const OtherType& Other);
        //Unary minus
        SimpleMatrix<TemplateType> operator-(void);
    //Times
        template <typename OtherType>
        SimpleMatrix<TemplateType> operator*(const SimpleMatrix<OtherType>& Other);
        template <typename OtherType>
        SimpleMatrix<TemplateType> operator*(const OtherType& Other);
    //Divide
        template <typename OtherType>
        SimpleMatrix<TemplateType> operator/(const SimpleMatrix<OtherType>& Other);
        template <typename OtherType>
        SimpleMatrix<TemplateType> operator/(const OtherType& Other);
        template <typename OtherType>
        SimpleMatrix<TemplateType> DivideByMatrix(const OtherType& Other);
    //Modulus
        template <typename OtherType>
        SimpleMatrix<TemplateType> operator%(const SimpleMatrix<OtherType>& Other);
        template <typename OtherType>
        SimpleMatrix<TemplateType> operator%(const OtherType& Other);
        template <typename OtherType>
        SimpleMatrix<TemplateType> ModulusByMatrix(const OtherType& Other);


    //Other operators
    //http://en.wikipedia.org/wiki/Operators_in_C_and_C%2B%2B
    // http://www.thegeekstuff.com/2013/09/cpp-operator-overloading/

    /// Apply a function to this matrix
    void apply(TemplateType (*FunctionPointer)(TemplateType));//Changes this matrix

    /// Display functions
    void display(void);
    void displayinfo(void);



};



/// Contructors
    template <typename TemplateType>
    SimpleMatrix<TemplateType>::SimpleMatrix(int xsize, int ysize)
    {
        resize(xsize, ysize);
    }

    template <typename TemplateType>
    SimpleMatrix<TemplateType>::SimpleMatrix(void)
    {
        xdimsize=1;
        ydimsize=1;
        values.resize(xdimsize);
        values[0].resize(ydimsize);
    }

    template <typename TemplateType>
    SimpleMatrix<TemplateType>::SimpleMatrix(vector<int> dimensions)
    {
        resize(dimensions);
    }

    template <typename TemplateType>
    void SimpleMatrix<TemplateType>::resize(int xsize, int ysize)
    {
        if (xsize<=0 || ysize<=0)
        {
            cout<<"Error: cannot create a matrix of size less than zero"<<endl;
            exit(-1);
        }
        xdimsize=xsize;
        ydimsize=ysize;
        values.resize(xdimsize);

        for (int i=0; i<xdimsize; i++)
        {
            values[i].resize(ydimsize);
        }
    }

    template <typename TemplateType>
    void SimpleMatrix<TemplateType>::resize(vector<int> dimensions)
    {
        if (dimensions.size()!=2)
        {
            cout<<"Error: cannot create a matrix which is larger or smaller than 2 dimensions"<<endl;
            exit(-1);
        }
        resize(dimensions[0], dimensions[1]);
    }





///Dimension checking
    template <typename TemplateType>
    vector<int> SimpleMatrix<TemplateType>::dim(void)
    {
        vector<int> DimSize;
        DimSize.push_back(xdimsize);
        DimSize.push_back(ydimsize);
        return DimSize;
    }

    template <typename TemplateType>
    int SimpleMatrix<TemplateType>::xsize(void)
    {
        return xdimsize;
    }

    template <typename TemplateType>
    int SimpleMatrix<TemplateType>::ysize(void)
    {
        return ydimsize;
    }

    template <typename TemplateType> template <typename OtherType>
    bool SimpleMatrix<TemplateType>::dimequal(SimpleMatrix<OtherType> Other)
    {
        if (xdimsize!=Other.xdimsize || ydimsize!=Other.ydimsize)
            return false;

        return true;//no problems
    }

    template <typename TemplateType> template <typename OtherType>
    void SimpleMatrix<TemplateType>::stop_if_dim_not_equal(SimpleMatrix<OtherType> Other)
    {
        if (dimequal(Other)==false)
        {
            cout<<"Error: dimensions incompatible ("<<xdimsize<<","<<ydimsize<<") and ("<<Other.xdimsize<<","<<Other.ydimsize<<")."<<endl;
            exit(-1);
        }
    }

///Matrix operations
    template <typename TemplateType>
    void SimpleMatrix<TemplateType>::setall(TemplateType SetValue)
    {
        for (int i=0; i<xdimsize; i++)
        {
            for (int j=0; j<ydimsize; j++)
            {
                values[i][j]=SetValue;
            }
        }
    }

    template <typename TemplateType>
    void SimpleMatrix<TemplateType>::transpose(void)
    {
        SimpleMatrix<TemplateType> NewMatrix(ydimsize, xdimsize);//doing this because it is the laziest way to make the proper sized matrix

        for (int i=0; i<xdimsize; i++)
        {
            for (int j=0; j<ydimsize; j++)
            {
                NewMatrix.values[j][i]=values[i][j];
            }
        }
        values=NewMatrix.values;
        xdimsize=NewMatrix.xdimsize;
        ydimsize=NewMatrix.ydimsize;
    }


/// Operator overloading
// http://en.wikibooks.org/wiki/C%2B%2B_Programming/Operators/Operator_Overloading
// In particular, we will be looking to overload the assignment operator to allow straighforward assignment of values
// http://en.wikibooks.org/wiki/C%2B%2B_Programming/Operators/Operator_Overloading#Assignment_operator
// we will also make use of the subscript operator []
// we may be able to use the subscript operator [][][] by iterating over the subscript operator multiple times
// http://stackoverflow.com/questions/6969881/operator-overload

// This source code has the basis for the overwhelming marjority of the operators that we wish to work on. Just search for "operator"
// https://gcc.gnu.org/onlinedocs/gcc-4.6.3/libstdc++/api/a01115_source.html

// Good tutorial on how this works: http://www.cprogramming.com/tutorial/operator_overloading.html

    ///Plus
        template <typename TemplateType> template <typename OtherType>
        SimpleMatrix<TemplateType> SimpleMatrix<TemplateType>::operator+(const SimpleMatrix<OtherType>& Other)
        {
            stop_if_dim_not_equal(Other);
            SimpleMatrix<TemplateType> ResultSM(xdimsize, ydimsize);
            for (int i=0; i<xdimsize; i++)
                for (int j=0; j<ydimsize; j++)
                    ResultSM.values[i][j]=values[i][j]+Other.values[i][j];
            return ResultSM;
        }

        //For other types
        template <typename TemplateType> template <typename OtherType>
        SimpleMatrix<TemplateType> SimpleMatrix<TemplateType>::operator+(const OtherType& Other)
        {
            SimpleMatrix<TemplateType> ResultSM(xdimsize, ydimsize);
            for (int i=0; i<xdimsize; i++)
                for (int j=0; j<ydimsize; j++)
                    ResultSM.values[i][j]=values[i][j]+Other;
            return ResultSM;
        }

        //Swapping for a discrete set of functions
        template <typename TemplateType> SimpleMatrix<TemplateType> operator+(char Other, SimpleMatrix<TemplateType> SMClass){return (SMClass + Other);}
        template <typename TemplateType> SimpleMatrix<TemplateType> operator+(short Other, SimpleMatrix<TemplateType> SMClass){return (SMClass + Other);}
        template <typename TemplateType> SimpleMatrix<TemplateType> operator+(int Other, SimpleMatrix<TemplateType> SMClass){return (SMClass + Other);}
        template <typename TemplateType> SimpleMatrix<TemplateType> operator+(long Other, SimpleMatrix<TemplateType> SMClass){return (SMClass + Other);}
        template <typename TemplateType> SimpleMatrix<TemplateType> operator+(long long Other, SimpleMatrix<TemplateType> SMClass){return (SMClass + Other);}
        template <typename TemplateType> SimpleMatrix<TemplateType> operator+(float Other, SimpleMatrix<TemplateType> SMClass){return (SMClass + Other);}
        template <typename TemplateType> SimpleMatrix<TemplateType> operator+(double Other, SimpleMatrix<TemplateType> SMClass){return (SMClass + Other);}
        template <typename TemplateType> SimpleMatrix<TemplateType> operator+(long double Other, SimpleMatrix<TemplateType> SMClass){return (SMClass + Other);}
        template <typename TemplateType> SimpleMatrix<TemplateType> operator+(bool Other, SimpleMatrix<TemplateType> SMClass){return (SMClass + Other);}

    ///Minus
        template <typename TemplateType> template <typename OtherType>
        SimpleMatrix<TemplateType> SimpleMatrix<TemplateType>::operator-(const SimpleMatrix<OtherType>& Other)
        {
            stop_if_dim_not_equal(Other);
            SimpleMatrix<TemplateType> ResultSM(xdimsize, ydimsize);
            for (int i=0; i<xdimsize; i++)
                for (int j=0; j<ydimsize; j++)
                    ResultSM.values[i][j]=values[i][j]-Other.values[i][j];
            return ResultSM;
        }

        //For other types
        template <typename TemplateType> template <typename OtherType>
        SimpleMatrix<TemplateType> SimpleMatrix<TemplateType>::operator-(const OtherType& Other)
        {
            SimpleMatrix<TemplateType> ResultSM(xdimsize, ydimsize);
            for (int i=0; i<xdimsize; i++)
                for (int j=0; j<ydimsize; j++)
                    ResultSM.values[i][j]=values[i][j]-Other;
            return ResultSM;
        }


        //Unary minus
        template <typename TemplateType>
        SimpleMatrix<TemplateType> SimpleMatrix<TemplateType>::operator-(void)
        {
            SimpleMatrix<TemplateType> ResultSM(xdimsize, ydimsize);
            for (int i=0; i<xdimsize; i++)
                for (int j=0; j<ydimsize; j++)
                    ResultSM.values[i][j]=-values[i][j];
            return ResultSM;
        }

        //Swapping for a discrete set of functions
        template <typename TemplateType> SimpleMatrix<TemplateType> operator-(char Other, SimpleMatrix<TemplateType> SMClass){return -(SMClass - Other);}
        template <typename TemplateType> SimpleMatrix<TemplateType> operator-(short Other, SimpleMatrix<TemplateType> SMClass){return -(SMClass - Other);}
        template <typename TemplateType> SimpleMatrix<TemplateType> operator-(int Other, SimpleMatrix<TemplateType> SMClass){return -(SMClass - Other);}
        template <typename TemplateType> SimpleMatrix<TemplateType> operator-(long Other, SimpleMatrix<TemplateType> SMClass){return -(SMClass - Other);}
        template <typename TemplateType> SimpleMatrix<TemplateType> operator-(long long Other, SimpleMatrix<TemplateType> SMClass){return -(SMClass - Other);}
        template <typename TemplateType> SimpleMatrix<TemplateType> operator-(float Other, SimpleMatrix<TemplateType> SMClass){return -(SMClass - Other);}
        template <typename TemplateType> SimpleMatrix<TemplateType> operator-(double Other, SimpleMatrix<TemplateType> SMClass){return -(SMClass - Other);}
        template <typename TemplateType> SimpleMatrix<TemplateType> operator-(long double Other, SimpleMatrix<TemplateType> SMClass){return -(SMClass - Other);}
        template <typename TemplateType> SimpleMatrix<TemplateType> operator-(bool Other, SimpleMatrix<TemplateType> SMClass){return -(SMClass - Other);}

    ///Times
        template <typename TemplateType> template <typename OtherType>
        SimpleMatrix<TemplateType> SimpleMatrix<TemplateType>::operator*(const SimpleMatrix<OtherType>& Other)
        {
            stop_if_dim_not_equal(Other);
            SimpleMatrix<TemplateType> ResultSM(xdimsize, ydimsize);
            for (int i=0; i<xdimsize; i++)
                for (int j=0; j<ydimsize; j++)
                    ResultSM.values[i][j]=values[i][j]*Other.values[i][j];
            return ResultSM;
        }

        //For other types
        template <typename TemplateType> template <typename OtherType>
        SimpleMatrix<TemplateType> SimpleMatrix<TemplateType>::operator*(const OtherType& Other)
        {
            SimpleMatrix<TemplateType> ResultSM(xdimsize, ydimsize);
            for (int i=0; i<xdimsize; i++)
                for (int j=0; j<ydimsize; j++)
                    ResultSM.values[i][j]=values[i][j]*Other;
            return ResultSM;
        }



        //Swapping for a discrete set of functions
        template <typename TemplateType> SimpleMatrix<TemplateType> operator*(char Other, SimpleMatrix<TemplateType> SMClass){return (SMClass * Other);}
        template <typename TemplateType> SimpleMatrix<TemplateType> operator*(short Other, SimpleMatrix<TemplateType> SMClass){return (SMClass * Other);}
        template <typename TemplateType> SimpleMatrix<TemplateType> operator*(int Other, SimpleMatrix<TemplateType> SMClass){return (SMClass * Other);}
        template <typename TemplateType> SimpleMatrix<TemplateType> operator*(long Other, SimpleMatrix<TemplateType> SMClass){return (SMClass * Other);}
        template <typename TemplateType> SimpleMatrix<TemplateType> operator*(long long Other, SimpleMatrix<TemplateType> SMClass){return (SMClass * Other);}
        template <typename TemplateType> SimpleMatrix<TemplateType> operator*(float Other, SimpleMatrix<TemplateType> SMClass){return (SMClass * Other);}
        template <typename TemplateType> SimpleMatrix<TemplateType> operator*(double Other, SimpleMatrix<TemplateType> SMClass){return (SMClass * Other);}
        template <typename TemplateType> SimpleMatrix<TemplateType> operator*(long double Other, SimpleMatrix<TemplateType> SMClass){return (SMClass * Other);}
        template <typename TemplateType> SimpleMatrix<TemplateType> operator*(bool Other, SimpleMatrix<TemplateType> SMClass){return (SMClass * Other);}

    ///Divide
        template <typename TemplateType> template <typename OtherType>
        SimpleMatrix<TemplateType> SimpleMatrix<TemplateType>::operator/(const SimpleMatrix<OtherType>& Other)
        {
            stop_if_dim_not_equal(Other);
            SimpleMatrix<TemplateType> ResultSM(xdimsize, ydimsize);
            for (int i=0; i<xdimsize; i++)
                for (int j=0; j<ydimsize; j++)
                    ResultSM.values[i][j]=values[i][j]/Other.values[i][j];
            return ResultSM;
        }

        //For other types
        template <typename TemplateType> template <typename OtherType>
        SimpleMatrix<TemplateType> SimpleMatrix<TemplateType>::operator/(const OtherType& Other)
        {
            SimpleMatrix<TemplateType> ResultSM(xdimsize, ydimsize);
            for (int i=0; i<xdimsize; i++)
                for (int j=0; j<ydimsize; j++)
                    ResultSM.values[i][j]=values[i][j]/Other;
            return ResultSM;
        }

        //Swapping for a discrete set of functions
        template <typename TemplateType> template <typename OtherType>
        SimpleMatrix<TemplateType> SimpleMatrix<TemplateType>::DivideByMatrix(const OtherType& Other)
        {
            SimpleMatrix<TemplateType> ResultSM(xdimsize, ydimsize);
            for (int i=0; i<xdimsize; i++)
                for (int j=0; j<ydimsize; j++)
                    ResultSM.values[i][j]=Other/values[i][j];
            return ResultSM;
        }
        template <typename TemplateType> SimpleMatrix<TemplateType> operator/(char Other, SimpleMatrix<TemplateType> SMClass){return SMClass.DivideByMatrix(Other);}
        template <typename TemplateType> SimpleMatrix<TemplateType> operator/(short Other, SimpleMatrix<TemplateType> SMClass){return SMClass.DivideByMatrix(Other);}
        template <typename TemplateType> SimpleMatrix<TemplateType> operator/(int Other, SimpleMatrix<TemplateType> SMClass){return SMClass.DivideByMatrix(Other);}
        template <typename TemplateType> SimpleMatrix<TemplateType> operator/(long Other, SimpleMatrix<TemplateType> SMClass){return SMClass.DivideByMatrix(Other);}
        template <typename TemplateType> SimpleMatrix<TemplateType> operator/(long long Other, SimpleMatrix<TemplateType> SMClass){return SMClass.DivideByMatrix(Other);}
        template <typename TemplateType> SimpleMatrix<TemplateType> operator/(float Other, SimpleMatrix<TemplateType> SMClass){return SMClass.DivideByMatrix(Other);}
        template <typename TemplateType> SimpleMatrix<TemplateType> operator/(double Other, SimpleMatrix<TemplateType> SMClass){return SMClass.DivideByMatrix(Other);}
        template <typename TemplateType> SimpleMatrix<TemplateType> operator/(long double Other, SimpleMatrix<TemplateType> SMClass){return SMClass.DivideByMatrix(Other);}
        template <typename TemplateType> SimpleMatrix<TemplateType> operator/(bool Other, SimpleMatrix<TemplateType> SMClass){return SMClass.DivideByMatrix(Other);}

    ///Modulus
        template <typename TemplateType> template <typename OtherType>
        SimpleMatrix<TemplateType> SimpleMatrix<TemplateType>::operator%(const SimpleMatrix<OtherType>& Other)
        {
            stop_if_dim_not_equal(Other);
            SimpleMatrix<TemplateType> ResultSM(xdimsize, ydimsize);
            for (int i=0; i<xdimsize; i++)
                for (int j=0; j<ydimsize; j++)
                    ResultSM.values[i][j]=values[i][j]%Other.values[i][j];
            return ResultSM;
        }

        //For other types
        template <typename TemplateType> template <typename OtherType>
        SimpleMatrix<TemplateType> SimpleMatrix<TemplateType>::operator%(const OtherType& Other)
        {
            SimpleMatrix<TemplateType> ResultSM(xdimsize, ydimsize);
            for (int i=0; i<xdimsize; i++)
                for (int j=0; j<ydimsize; j++)
                    ResultSM.values[i][j]=values[i][j]%Other;
            return ResultSM;
        }

        //Swapping for a discrete set of functions
        template <typename TemplateType> template <typename OtherType>
        SimpleMatrix<TemplateType> SimpleMatrix<TemplateType>::ModulusByMatrix(const OtherType& Other)
        {
            SimpleMatrix<TemplateType> ResultSM(xdimsize, ydimsize);
            for (int i=0; i<xdimsize; i++)
                for (int j=0; j<ydimsize; j++)
                    ResultSM.values[i][j]=Other%values[i][j];
            return ResultSM;
        }


        template <typename TemplateType> SimpleMatrix<TemplateType> operator%(char Other, SimpleMatrix<TemplateType> SMClass){return SMClass.ModulusByMatrix(Other);}
        template <typename TemplateType> SimpleMatrix<TemplateType> operator%(short Other, SimpleMatrix<TemplateType> SMClass){return SMClass.ModulusByMatrix(Other);}
        template <typename TemplateType> SimpleMatrix<TemplateType> operator%(int Other, SimpleMatrix<TemplateType> SMClass){return SMClass.ModulusByMatrix(Other);}
        template <typename TemplateType> SimpleMatrix<TemplateType> operator%(long Other, SimpleMatrix<TemplateType> SMClass){return SMClass.ModulusByMatrix(Other);}
        template <typename TemplateType> SimpleMatrix<TemplateType> operator%(long long Other, SimpleMatrix<TemplateType> SMClass){return SMClass.ModulusByMatrix(Other);}
        template <typename TemplateType> SimpleMatrix<TemplateType> operator%(float Other, SimpleMatrix<TemplateType> SMClass){return SMClass.ModulusByMatrix(Other);}
        template <typename TemplateType> SimpleMatrix<TemplateType> operator%(double Other, SimpleMatrix<TemplateType> SMClass){return SMClass.ModulusByMatrix(Other);}
        template <typename TemplateType> SimpleMatrix<TemplateType> operator%(long double Other, SimpleMatrix<TemplateType> SMClass){return SMClass.ModulusByMatrix(Other);}
        template <typename TemplateType> SimpleMatrix<TemplateType> operator%(bool Other, SimpleMatrix<TemplateType> SMClass){return SMClass.ModulusByMatrix(Other);}



//Apply a function to the matrix
template <typename TemplateType>
void SimpleMatrix<TemplateType>::apply(TemplateType (*FunctionPointer)(TemplateType))
{
    for (int i=0; i<xdimsize; i++)
        for (int j=0; j<ydimsize; j++)
            values[i][j]=FunctionPointer(values[i][j]);
}

//Apply a function to be returned
template <typename ReturnTemplateType, typename TemplateType>
SimpleMatrix<ReturnTemplateType> apply(ReturnTemplateType (*FunctionPointer)(TemplateType), SimpleMatrix<TemplateType> A)
{
    TemplateType TempResultStore;
    //Determine size of input vector
    int xdimsize=A.xsize();
    int ydimsize=A.ysize();
    SimpleMatrix<ReturnTemplateType> ResultSM(xdimsize, ydimsize);
    //for all the elements of A
    for (int i=0; i<xdimsize; i++)
    {
        for (int j=0; j<ydimsize; j++)
        {
            TempResultStore=FunctionPointer(A(i, j));
            ResultSM(i, j)=TempResultStore;
        }
    }
    return ResultSM;
}



//applying a function to 2 multidimensional matrices
template <typename ReturnTemplateType, typename InputTemplateTypeA, typename InputTemplateTypeB>
SimpleMatrix<ReturnTemplateType> apply(ReturnTemplateType (*FunctionPointer)(InputTemplateTypeA, InputTemplateTypeB), SimpleMatrix<InputTemplateTypeA> A, SimpleMatrix<InputTemplateTypeB> B)
{
    A.stop_if_dim_not_equal(B);
    ReturnTemplateType TempResultStore;
    int xdimsize=A.xsize();
    int ydimsize=A.ysize();
    SimpleMatrix<ReturnTemplateType> ResultSM(xdimsize, ydimsize);

    //for all the elements of A
    for (int i=0; i<xdimsize; i++)
    {
        for (int j=0; j<ydimsize; j++)
        {
            TempResultStore=FunctionPointer(A(i, j),  B(i, j));
            ResultSM(i, j)=TempResultStore;
        }
    }
    return ResultSM;
}



//Display functions
template <typename TemplateType>
void SimpleMatrix<TemplateType>::display(void)
{
    cout<<"Contents: "<<endl;
    for (int j=0; j<ydimsize; j++)
    {
        for (int i=0; i<xdimsize; i++)
            cout<<values[i][j]<<", ";
        cout<<endl;
    }

}

template <typename TemplateType>
void SimpleMatrix<TemplateType>::displayinfo(void)
{
    cout<<"Dimensions: ( "<< xdimsize << ", " << ydimsize <<")"<<endl;

    cout<<"Contents summary: "<<endl;
    for (int j=0; j<ydimsize && j<5 ; j++)//limit to a 5 by 5 display of content
    {
        for (int i=0; i<xdimsize && i<5; i++)
            cout<<values[i][j]<<", ";
        cout<<endl;
    }
    cout<<"..."<<endl;
    cout<<"To see full contents use display()"<<endl<<endl;
}














template <typename TemplateType>
SimpleMatrix<TemplateType> xjoin(SimpleMatrix<TemplateType> A, SimpleMatrix<TemplateType> B)
{
    //check that the y dimension is equal
    int Axsize=A.xsize();
    int Bxsize=B.xsize();
    int Aysize=A.ysize();
    int Bysize=B.ysize();

    //if the dimensions are incorrect
    if (Aysize!=Bysize)
    {
        cout<<"Incorrect dimensions used in xjoin ("<<Axsize<<", "<< Aysize <<") & ("<< Bxsize<<", "<<Bysize<<")." <<endl;
        exit(-1);
    }

    SimpleMatrix<TemplateType> ReturnMatrix;
    ReturnMatrix=A;
    ReturnMatrix.resize(Axsize+Bxsize, Aysize);

    for (int i=0; i<Bxsize; i++)
    {
        for (int j=0; j<Bysize; j++)
        {
            ReturnMatrix(i+Axsize, j)=B(i, j);
        }
    }
    return ReturnMatrix;
}

template <typename TemplateType>
SimpleMatrix<TemplateType> yjoin(SimpleMatrix<TemplateType> A, SimpleMatrix<TemplateType> B)
{
    //check that the x dimension is equal
    int Axsize=A.xsize();
    int Bxsize=B.xsize();
    int Aysize=A.ysize();
    int Bysize=B.ysize();

    //if the dimensions are incorrect
    if (Axsize!=Bxsize)
    {
        cout<<"Incorrect dimensions used in yjoin ("<<Axsize<<", "<< Aysize <<") & ("<< Bxsize<<", "<<Bysize<<")." <<endl;
        exit(-1);
    }

    SimpleMatrix<TemplateType> ReturnMatrix;
    ReturnMatrix=A;
    ReturnMatrix.resize(Axsize, Aysize+Bysize);

    for (int i=0; i<Bxsize; i++)
    {
        for (int j=0; j<Bysize; j++)
        {
            ReturnMatrix(i, j+Aysize)=B(i, j);
        }
    }
    return ReturnMatrix;
}




/*
Boost Software License - Version 1.0 - August 17, 2003

Permission is hereby granted, free of charge, to any person or organization
obtaining a copy of the software and accompanying documentation covered by
this license (the "Software") to use, reproduce, display, distribute,
execute, and transmit the Software, and to prepare [[derivative work]]s of the
Software, and to permit third-parties to whom the Software is furnished to
do so, all subject to the following:

The copyright notices in the Software and this entire statement, including
the above license grant, this restriction and the following disclaimer,
must be included in all copies of the Software, in whole or in part, and
all derivative works of the Software, unless such copies or derivative
works are solely in the form of machine-executable object code generated by
a source language processor.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
DEALINGS IN THE SOFTWARE.
*/
