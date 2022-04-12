#include "doctest.h"
#include "Matrix.hpp"
using namespace zich;
using namespace std;

TEST_CASE("Matrix sizes ilegal for operator - check for exceptions"){
    std::vector<double> arr1 = {0, 0, 0, 0};
    std::vector<double> arr2 = {0, 0, 0, 0, 0, 0};

    Matrix m1(arr1, 2 ,2); // 2X2
    Matrix m2(arr2, 3, 2);  // 3x2

    CHECK_THROWS(m1 * m2);

    CHECK_THROWS(m1 + m2);
    CHECK_THROWS(m2 + m1);

    CHECK_THROWS(m1 - m2);
    CHECK_THROWS(m2 - m1);

    bool ans=true;

    CHECK_THROWS(ans = (m1 > m2));
    CHECK_THROWS(ans = (m2 > m1));

    CHECK_THROWS(ans = (m1 < m2));
    CHECK_THROWS(ans = (m2 < m1));

    CHECK_THROWS(ans = (m1 >= m2));
    CHECK_THROWS(ans = (m2 >= m1));

    CHECK_THROWS(ans = (m1 <= m2));
    CHECK_THROWS(ans = (m2 <= m1));

    CHECK_THROWS(ans = (m1 == m2));
    CHECK_THROWS(ans = (m2 == m1));

    CHECK_THROWS(ans = (m1 != m2));
    CHECK_THROWS(ans = (m2 != m1));
    
}

TEST_CASE("Good input - no exceptions"){
    std::vector<double> yehida_arr = {1, 0, 0, 1};
    std::vector<double> arr1 = {0, 0, 0, 0};
    std::vector<double> arr2 = {1, 1, 1, 1};


    std::vector<double> ans1 = {-1, -1, -1, -1};
    std::vector<double> ans2 = {2, 2, 2, 2};
    std::vector<double> ans3 = {-4, -4, -4, -4};

    Matrix yehida(yehida_arr, 2 ,2);
    Matrix mat1(arr1, 2, 2);
    Matrix mat2(arr2, 2 , 2);
    Matrix mat3(ans1, 2 , 2);
    Matrix mat4(ans2, 2 , 2);
    Matrix mat5(ans3, 2 , 2);

    CHECK(((mat1 + mat2) == mat2));
    CHECK(((mat2 + mat1) == mat2));
    
    CHECK(((mat1+=mat2) == mat2));
    CHECK(((mat2+=mat1) == mat2));
    
    CHECK((+mat1)==mat1);
    CHECK((+mat2)==mat2);

    CHECK(((mat1 - mat2) == mat3));
    CHECK(((mat2 - mat1) == mat2));
    
    CHECK(((mat1-=mat2) == mat3));
    CHECK(((mat2-=mat1) == mat2));
    
    CHECK((-mat1)==mat1);
    CHECK((-mat2)==mat3);

    CHECK_EQ(true,(mat1 < mat2));
    CHECK_EQ(true,(mat1<=mat2));
    CHECK_EQ(true,(mat1<=mat1));

    CHECK_EQ(true,(mat2>mat1));
    CHECK_EQ(true,(mat2>=mat1));
    CHECK_EQ(true,(mat2>=mat2));
    
    CHECK_EQ(true,(mat1==mat1));

    CHECK_EQ(true,(mat2!=mat1));

    CHECK((mat1++) == mat2);
    CHECK((++mat1) == mat2);

    CHECK((mat2--) == mat1);
    CHECK((--mat2) == mat1);

    CHECK((mat2*2) == mat4);
    CHECK((mat3*(-2)) == mat4);
    CHECK((mat4*0.5) == mat2);

    CHECK((mat3*mat4) == mat5);


}
