#include <iostream>
#include <bitset>
#include <iostream>
#include <cmath>
#include <bits/stdc++.h>
#include <vector>
#include <string>
#define M 64
#include "carRecord.h"
using namespace std; 


template<typename typeRecord>
struct extendibleHash {
private:
    string hashIndexFile;
     int  GlobalDepth;
     int BlockingFactor;

    string convertBinary(long key,  int length){
        string binary= bitset<M>(key).to_string();
        return binary.substr(M - length, length);
    }

    template <typename KeyType>
    string generateHash(KeyType key,  int length){
         if (typeid(key) == typeid(int()) || typeid(key) == typeid(long()) || typeid(key) == typeid(double()) ||
           typeid(key) == typeid(float()) || typeid(key) == typeid(()) || typeid(key)== typeid(char())){
            long newKey = long (key) % int(pow(2, GlobalDepth));
            return convertBinary(newKey, length);
        }
        else if (typeid(key)== typeid(string())){
            long newKey = long (stoi("key") ) % int( pow(2, GlobalDepth));
            return convertBinary(newKey, length);
        }
        else{
            return convertBinary(key, length); 
        }
    }


    void initializeBuckets(){
        //cabecerea
        int deleteNext = -1;
        int totalRecords = 0;
        //files
        fstream bucketOne;
        fstream bucketZero; 
        bucketOne.open("1.dat", ios::binary | ios::out | fstream::in);
        bucketOne.write((char *) &totalRecords, sizeof(int));
        bucketOne.write((char *) &deleteNext, sizeof(int));
        bucketZero.open("0.dat", ios::binary | ios::out | fstream::in );
        bucketZero.write((char *) &totalRecords, sizeof(int));
        bucketZero.write((char *) &deleteNext, sizeof(int));
        bucketOne.close();
        bucketZero.close();
    }

    public:

    void writeIndex(fstream &indexFile, long depth){
        string index;
        for( int i = 0; i< pow(2,  this->globalDepth-1); i++){
            index = generateHash (i ,  this->globalDepth);
            char array[ this->globalDepth];
            strcpy(array, index.c_str());
            indexFile.write((char*)&array,sizeof(char)*globalDepth);
            indexFile.write((char*)&depth,sizeof(long));
        }
        indexFile.close();
    }
    
    void deleteInfoFile(string indexFile) {
         int registers =0; int delete = -1; 
        ofstream file; file.open(indexFile,  ofstream::trunc |ofstream::out );
        // Trunc to 0 registers, and deleteNext is -1
        file.write((char *) &registers, sizeof( int));
        file.write((char *) &delete, sizeof(int));
        file.close();
    }



    extendibleHash( int GlobalDepth, const string& hashIndexFile,   int BlockingFactor) {
        fstream indexFile;
        this->hashIndexFile = move(hashIndexFile);
        this->GlobalDepth = GlobalDepth;
        this->BlockingFactor = BlockingFactor;
        indexFile.open(this->hashIndexFile, ios::binary | ios::out);
        writeIndex( indexFile, 1);
        initializeBuckets(); 
    }

    void rebuild_index_file(std::string bucket) {
        std::fstream index_file(hashIndexFile, std::ios::binary | std::ios::in | std::ios::out);
        char *name = new char[MAX_DEPTH];
        std::string new_name;
        for (int i = 0; i < pow(2, MAX_DEPTH); ++i) {
            index_file.seekg(0, std::ios::beg);
            index_file.seekg((i * MAX_DEPTH * 2));
            index_file.read(name, sizeof(char) * MAX_DEPTH);
            std::string str(name);
            if (str.substr(str.length() - bucket.length()) == bucket) {
                new_name = std::string(1, str[str.length() - bucket.length() - 1]) + bucket;
                index_file.seekg((i * MAX_DEPTH * 2) + MAX_DEPTH);
                char array[MAX_DEPTH];
                strcpy(array, new_name.c_str());
                index_file.write(array, sizeof(char) * MAX_DEPTH);
            }
        }
        index_file.close();
    }

    void split(string bucket) {
        //create new buckets 
        string bucketZero, bucketOne; 
        fstream fileZero, fileOne; 
        int totalRecords = 0; int deleteNext = -1;
        bucketZero ="0" + bucket + ".dat";        
        bucketOne = "1" + bucket + ".dat";
        fileZero.open(bucketZero, ios::binary | ios::out | fstream::in);
        fileOne.open(bucketOne, ios::binary | ios::out | fstream::in);        
        fileZero.write((char *) &totalRecords, sizeof(int));
        fileZero.write((char *) &deleteNext, sizeof(int));
        fileOne.write((char *) &totalRecords, sizeof(int));
        fileOne.write((char *) &deleteNext, sizeof(int));
        fileZero.close();
        fileOne.close();
        //rebuilt index file

    }


    void insertRecord(Car carRecord) {
      /*  fstream indexFile(hashIndexFile, ios::binary | ios::in);
        indexFile.seekg(((2* GlobalDepth) * generateHash(carRecord.id, GlobalDepth) ) + GlobalDepth);
        char *file = new char[GlobalDepth];
        indexFile.read(file, sizeof(char) * GlobalDepth);
        string str(file);
        indexFile.close();
        string bucket= get_bucket_with_key(key_to_insert);
        string bucketFile =  bucket + ".dat";
        */
    //
        fstream fileOfBucket(bucketFile, ios::binary | ios::in | ios::out);
        int totalRecords, deleteNext;
        fileOfBucket.read((char *) &totalRecords, sizeof(int));
        fileOfBucket.read((char *) &deleteNext, sizeof(int));
        if (totalRecords >= BlockingFactor) {
            if (bucket.length() < GlobalDepth) { 
                /*if reach number of records allow in a block and the local depth didn´t
                 exceeded the globaldepth, split the buckets      */      
                split(bucket);
     
            }
            else {
                //if no more splits are allow due to the GlobalDepth add to the end 
                ++totalRecords;
                fileOfBucket.seekg(0, ios::beg);
                fileOfBucket.write((char *) &totalRecords, sizeof(int));
                fileOfBucket.seekg(0, ios::end);
                fileOfBucket.write((char *) &carRecord, sizeof(Car));

            }
        } 

        else {    
            //update the number of total records         
            ++totalRecords; 
            fileOfBucket.seekg(0, ios::beg);
            fileOfBucket.write((char *) &totalRecords, sizeof(int));
            // if there's no deleted record add to the end 
            if (deleteNext == -1) {
                fileOfBucket.seekg(0, ios::end);
                fileOfBucket.write((char *) &carRecord, sizeof(Car));
            } 
            else {
                fileOfBucket.seekg((2 * sizeof(int)) + ((deleteNext - 1) * sizeof(Car)));
                Car deletedRecord;
                // LIFO technique, so insert in the first deleted record 
                fileOfBucket.read((char *) &deletedRecord, sizeof(Car));
                int deleteNextDeletedRecord = deletedRecord.nextDel;
                fileOfBucket.seekg((2 * sizeof(int)) + ((deleteNext - 1) * sizeof(Car)));
                fileOfBucket.write((char *) &carRecord, sizeof(Car));
                fileOfBucket.seekg(sizeof(int));
                fileOfBucket.write((char *) &deleteNextDeletedRecord, sizeof(int));
            }
        }

        fileOfBucket.close();
    }
    
    };
