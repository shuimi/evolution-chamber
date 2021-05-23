//
// Created by Vladimir on 20.05.2021.
//

#ifndef GENETIC_ALGS_GEN_H
#define GENETIC_ALGS_GEN_H


#include <vector>
#include <string>

class Gen {
private:
    int radix;
    bool negative;
    std::vector<char> integer_digits;
    std::vector<char> fractional_digits;

    int ascii_cast(char symbol){
        return symbol - '0';
    }

    void parse(std::string value){

        if(value.empty()) return;

        int i = 0;

        if(value[0] == '-'){
            setNegative(true);
            i = 1;
        }

        for(; i < value.length(); i++){

            if(value[i] != '.'){
                if (!(value[i] >= '0' && value[i] <= '9' || value[i] >= 'A' && value[i] <= 'Z')){
                    throw "[invalid value error]: one of symbols is not digit 0..9 or literal A..Z";
                }
                if(ascii_cast(value[i]) >= this->radix){
                    throw "[invalid value error]: one of digits is equal or bigger than radix";
                }
            }
        }

        if(value[0] == '-'){
            i = 1;
        }else{
            i = 0;
        }

        if(value.find('.')){
            for(; value[i] != '.'; i++){
                this->integer_digits.push_back(value[i]);
            }
            i++;
            for(; i < value.length(); i++){
                this->fractional_digits.push_back(value[i]);
            }
        }
        else{
            for(char symbol : value){
                this->integer_digits.push_back(symbol);
            }
        }

    }

public:

    explicit Gen(int radix): radix(radix), negative(false) {

    }

    Gen(int radix, std::string value): radix(radix), negative(false) {
        this->set(value);
    }

    void set(std::string value){
        this->parse(value);
    }

    bool isNegative() const {
        return negative;
    }

    void setNegative(bool negative) {
        Gen::negative = negative;
    }

//    bool operator<(const Gen &rhs) const {
//        return true;
//    }
//
//    bool operator>(const Gen &rhs) const {
//        return rhs < *this;
//    }
//
//    bool operator<=(const Gen &rhs) const {
//        return !(rhs < *this);
//    }
//
//    bool operator>=(const Gen &rhs) const {
//        return !(*this < rhs);
//    }
//
//    bool operator==(const Gen &rhs) const {
//        return radix == rhs.radix &&
//               negative == rhs.negative &&
//               integer_digits == rhs.integer_digits &&
//               fractional_digits == rhs.fractional_digits;
//    }
//
//    bool operator!=(const Gen &rhs) const {
//        return !(rhs == *this);
//    }

    std::string get(){
        std::string output;
        if(negative) output.push_back('-');
        for(char digit : integer_digits){
            output.push_back(digit);
        }
        output.push_back('.');
        for(char digit : fractional_digits){
            output.push_back(digit);
        }
        return output;
    }

//    Gen* operator + (Gen gen) {
//
//        Gen* result;
//
//
//    }


//    Gen operator - (T v) { return TypeWrapper( value - v); }
//    Gen operator * (T v) { return TypeWrapper( value * v); }
//    Gen operator / (T v) { return TypeWrapper( value / v); }
//    Gen operator % (T v) { return TypeWrapper( value % v); }
//
//    void operator += (T v) { value += v; }
//    void operator -= (T v) { value -= v; }
//    void operator *= (T v) { value *= v; }
//    void operator /= (T v) { value /= v; }
//    void operator %= (T v) { value %= v; }
//
//    T operator ++ () { return ++value; }
//    T operator -- () { return --value;}
//    T operator ++ (int v) { return value++; }
//    T operator -- (int v) { return value--; }

//    std::string view_dec(){
//
//    }
//
//    std::string view_bin(){
//
//    }
//
//    std::string view_hex(){
//
//    }
//
//    std::string view_oct(){
//
//    }

};


#endif //GENETIC_ALGS_GEN_H
