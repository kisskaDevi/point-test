#include <iostream>
#include <utility>

template <typename type>
float getValue(type values, size_t i){
    return *(reinterpret_cast<float*>(&values) + i);
}

struct vec2{float x,y;};
struct vec3{float x,y,z;};
struct vec4{float x,y,z,w;};

float getDecrementVec(const vec2& v){return v.x;}
float getLastVal(const vec2& v){return v.y;}
vec2 getVec(const float& x, const float& y){return vec2{x,y};}

vec2 getDecrementVec(const vec3& v){return vec2{v.x,v.y};}
float getLastVal(const vec3& v){return v.z;}
vec3 getVec(const vec2& v, const float& z){return vec3{v.x,v.y,z};}

vec3 getDecrementVec(const vec4& v){return vec3{v.x,v.y,v.z};}
float getLastVal(const vec4& v){return v.w;}
vec4 getVec(const vec3& v, const float& w){return vec4{v.x,v.y,v.z,w};}

template <typename vecN>
bool operator<(vecN L, vecN R){
    return getDecrementVec(L) < getDecrementVec(R) && getLastVal(L) < getLastVal(R);  
}

template <typename vecN>
vecN& operator+=(vecN& L, const vecN& R){
    auto vec = getDecrementVec(L); vec += getDecrementVec(R);
    float scal = getLastVal(L) + getLastVal(R);
    return L = getVec(vec, scal);
}

template <typename vecType, std::enable_if_t<std::is_same<vecType,vec2>::value ||
                                             std::is_same<vecType,vec3>::value ||
                                             std::is_same<vecType,vec4>::value , bool> = true>
struct point{
    vecType coord;

    point(const vecType& p):coord(p){}

    template <typename vecN>
    bool operator<(vecN R){
        return coord < R;  
    }
    template <typename vecN>
    vecN& operator+=(vecN& R){
        return coord = (coord += R);  
    }
};

using vecN = vec4;
int main(){
    point<vecN> p(vecN{1.0f, 2.0f, 3.0f, 5.0f});
    vecN             v{2.0f,-3.0f, 5.0f, 1.0f};
    p+=v;
    std::cout << p.coord.x << '\t' << p.coord.y << '\t' << p.coord.z << '\t' << p.coord.w << std::endl;
}