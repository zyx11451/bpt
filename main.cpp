//bpt
#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include <string>
const int disk_block_size=4096;
namespace king_zyx{
    class exception {
    protected:
        const std::string variant = "";
        std::string detail = "";
    public:
        exception() {}
        exception(const exception &ec) : variant(ec.variant), detail(ec.detail) {}
        virtual std::string what() {
            return variant + " " + detail;
        }
    };

    class index_out_of_bound : public exception {
        /* __________________________ */
    };

    class runtime_error : public exception {
        /* __________________________ */
    };

    class invalid_iterator : public exception {
        /* __________________________ */
    };

    class container_is_empty : public exception {
        /* __________________________ */
    };

    template<typename T>
    class vector
    {
    private:
        T* data;
        int len;
        int capacity;
        void doubleSpace(){
            capacity*=2;
            //加1是为了留出end（），下同
            T* temp=static_cast<T*>(malloc((capacity+1)* sizeof(T)));
            for(int i=0;i<len;++i){
                new(temp+i) T(*(data+i));
                (data+i)->~T();
            }
            free(data);
            data=temp;
        };
    public:
        /**
         * TODO
         * a type for actions of the elements of a vector, and you should write
         *   a class named const_iterator with same interfaces.
         */
        /**
         * you can see RandomAccessIterator at CppReference for help.
         */
        class const_iterator;
        class iterator
        {
            // The following code is written for the C++ type_traits library.
            // Type traits is a C++ feature for describing certain properties of a type.
            // For instance, for an iterator, iterator::value_type is the type that the
            // iterator points to.
            // STL algorithms and containers may use these type_traits (e.g. the following
            // typedef) to work properly. In particular, without the following code,
            // @code{std::sort(iter, iter1);} would not compile.
            // See these websites for more information:
            // https://en.cppreference.com/w/cpp/header/type_traits
            // About value_type: https://blog.csdn.net/u014299153/article/details/72419713
            // About iterator_category: https://en.cppreference.com/w/cpp/iterator
        public:
            using difference_type = std::ptrdiff_t;
            using value_type = T;
            using pointer = T*;
            using reference = T&;
            using iterator_category = std::output_iterator_tag;

        private:
            /**
             * TODO add data members
             *   just add whatever you want.
             */

            vector<T>* belongs_to_which_vector;

        public:
            T* pt;
            iterator(T* pt_,vector<T>* x){
                pt=pt_;
                belongs_to_which_vector=x;
            }
            /**
             * return a new iterator which pointer n-next elements
             * as well as operator-
             */
            iterator operator+(const int &n) const
            {
                //TODO
                iterator ans(pt+n,belongs_to_which_vector);
                return ans;
            }
            iterator operator-(const int &n) const
            {
                //TODO
                iterator ans(pt-n,belongs_to_which_vector);
                return ans;
            }
            // return the distance between two iterators,
            // if these two iterators point to different vectors, throw invaild_iterator.
            int operator-(const iterator &rhs) const
            {
                //TODO
                if(rhs.belongs_to_which_vector!=belongs_to_which_vector) throw invalid_iterator();
                return pt-rhs.pt;
            }
            iterator& operator+=(const int &n)
            {
                //TODO
                pt+=n;
                return *this;
            }
            iterator& operator-=(const int &n)
            {
                //TODO
                pt-=n;
                return *this;
            }
            /**
             * TODO iter++
             */
            iterator operator++(int) {
                iterator temp(pt,belongs_to_which_vector);
                pt++;
                return temp;
            }
            /**
             * TODO ++iter
             */
            iterator& operator++() {
                pt++;
                return *this;
            }
            /**
             * TODO iter--
             */
            iterator operator--(int) {
                iterator temp(pt,belongs_to_which_vector);
                pt--;
                return temp;
            }
            /**
             * TODO --iter
             */
            iterator& operator--() {
                pt--;
                return *this;
            }
            /**
             * TODO *it
             */
            T& operator*() const{
                return *pt;
            }
            /**
             * a operator to check whether two iterators are same (pointing to the same memory address).
             */
            bool operator==(const iterator &rhs) const {
                return (pt==rhs.pt)&&(belongs_to_which_vector==rhs.belongs_to_which_vector);
            }
            bool operator==(const const_iterator &rhs) const {
                return (pt==rhs.pt)&&(belongs_to_which_vector==rhs.belongs_to_which_vector);
            }
            /**
             * some other operator for iterator.
             */
            bool operator!=(const iterator &rhs) const {
                return !((pt==rhs.pt)&&(belongs_to_which_vector==rhs.belongs_to_which_vector));
            }
            bool operator!=(const const_iterator &rhs) const {
                return !((pt==rhs.pt)&&(belongs_to_which_vector==rhs.belongs_to_which_vector));
            }
        };
        /**
         * TODO
         * has same function as iterator, just for a const object.
         */
        class const_iterator
        {
        public:
            using difference_type = std::ptrdiff_t;
            using value_type = T;
            using pointer = T*;
            using reference = T&;
            using iterator_category = std::output_iterator_tag;

        private:
            /*TODO*/


        public:
            const T*  pt;
            const vector<T>* belongs_to_which_vector;
            /**
     * return a new iterator which pointer n-next elements
     * as well as operator-
     */
            const_iterator operator+(const int &n) const
            {
                //TODO
                const_iterator ans;
                ans.pt=pt+n;
                ans.belongs_to_which_vector=belongs_to_which_vector;
                return ans;
            }
            const_iterator operator-(const int &n) const
            {
                //TODO
                const_iterator ans;
                ans.pt=pt-n;
                ans.belongs_to_which_vector=belongs_to_which_vector;
                return ans;
            }
            // return the distance between two iterators,
            // if these two iterators point to different vectors, throw invaild_iterator.
            int operator-(const const_iterator &rhs) const
            {
                //TODO
                if(rhs.belongs_to_which_vector!=belongs_to_which_vector) throw invalid_iterator();
                return pt-rhs.pt;
            }
            const_iterator& operator+=(const int &n)
            {
                //TODO
                pt+=n;
                return *this;
            }
            const_iterator& operator-=(const int &n)
            {
                //TODO
                pt-=n;
                return *this;
            }
            /**
             * TODO iter++
             */
            const_iterator operator++(int) {
                const_iterator temp;
                temp.pt=pt;
                temp.belongs_to_which_vector=belongs_to_which_vector;
                pt++;
                return temp;
            }
            /**
             * TODO ++iter
             */
            const_iterator& operator++() {
                pt++;
                return *this;
            }
            /**
             * TODO iter--
             */
            const_iterator operator--(int) {
                const_iterator temp;
                temp.pt=pt;
                temp.belongs_to_which_vector=belongs_to_which_vector;
                return temp;
            }
            /**
             * TODO --iter
             */
            const_iterator& operator--() {
                pt--;
                return *this;
            }
            /**
             * TODO *it
             */
            const T& operator*() const{
                return *pt;
            }
            /**
             * a operator to check whether two iterators are same (pointing to the same memory address).
             */
            bool operator==(const iterator &rhs) const {
                return (pt==rhs.pt)&&(belongs_to_which_vector==rhs.belongs_to_which_vector);
            }
            bool operator==(const const_iterator &rhs) const {
                return (pt==rhs.pt)&&(belongs_to_which_vector==rhs.belongs_to_which_vector);
            }
            /**
             * some other operator for iterator.
             */
            bool operator!=(const iterator &rhs) const {
                return !((pt==rhs.pt)&&(belongs_to_which_vector==rhs.belongs_to_which_vector));
            }
            bool operator!=(const const_iterator &rhs) const {
                return !((pt==rhs.pt)&&(belongs_to_which_vector==rhs.belongs_to_which_vector));
            }
        };
        /**
         * TODO Constructs
         * At least two: default constructor, copy constructor
         */
        vector() {
            capacity=1;
            len=0;
            data=static_cast<T *>(malloc(2*sizeof(T)));
        }
        vector(const vector &other) {
            capacity=other.capacity;
            len=other.len;
            data=static_cast<T *>(malloc((capacity+1)*sizeof(T)));
            for(int i=0;i<len;++i){
                new(data+i) T(*(other.data+i));
            }
        }
        /**
         * TODO Destructor
         */
        ~vector() {
            for(int i=0;i<len;++i){
                (data+i)->~T();
            }
            free(data);
        }
        /**
         * TODO Assignment operator
         */
        vector &operator=(const vector &other) {
            if(other.data==data) return *this;
            free(data);
            capacity=other.capacity;
            len=other.len;

            data=static_cast<T *>(malloc((capacity+1)*sizeof(T)));
            for(int i=0;i<len;++i){
                new(data+i) T(*(other.data+i));
            }
            return *this;
        }
        /**
         * assigns specified element with bounds checking
         * throw index_out_of_bound if pos is not in [0, size)
         */
        T & at(const size_t &pos) {
            if(pos<0||pos>=len) throw index_out_of_bound();
            return *(data+pos);
        }
        const T & at(const size_t &pos) const {
            if(pos<0||pos>=len) throw index_out_of_bound();
            return *(data+pos);
        }
        /**
         * assigns specified element with bounds checking
         * throw index_out_of_bound if pos is not in [0, size)
         * !!! Pay attentions
         *   In STL this operator does not check the boundary but I want you to do.
         */
        T & operator[](const size_t &pos) {
            if(pos<0||pos>=len) throw index_out_of_bound();
            return *(data+pos);
        }
        const T & operator[](const size_t &pos) const {
            if(pos<0||pos>=len) throw index_out_of_bound();
            return *(data+pos);
        }
        /**
         * access the first element.
         * throw container_is_empty if size == 0
         */
        const T & front() const {
            if(len==0) throw container_is_empty();
            return *data;
        }
        /**
         * access the last element.
         * throw container_is_empty if size == 0
         */
        const T & back() const {
            if(len==0) throw container_is_empty();
            return *(data+len-1);
        }
        /**
         * returns an iterator to the beginning.
         */
        iterator begin() {
            iterator ans(data, this);
            return ans;
        }
        const_iterator cbegin() const {
            const_iterator ans;
            ans.pt=data;
            ans.belongs_to_which_vector= this;
            return ans;
        }
        /**
         * returns an iterator to the end.
         */
        iterator end() {
            iterator ans(data+len, this);
            return ans;
        }
        const_iterator cend() const {
            const_iterator ans;
            ans.pt=data+len;
            ans.belongs_to_which_vector= this;
            return ans;
        }
        /**
         * checks whether the container is empty
         */
        bool empty() const {
            return len==0;
        }
        /**
         * returns the number of elements
         */
        size_t size() const {
            return len;
        }
        /**
         * clears the contents
         */
        void clear() {
            for(int i=0;i<len;++i){
                (data+i)->~T();
            }
            free(data);
            capacity=1;
            len=0;
            data=static_cast<T *>(malloc(2*sizeof(T)));

        }
        /**
         * inserts value before pos
         * returns an iterator pointing to the inserted value.
         */
        iterator insert(iterator pos, const T &value) {
            if(capacity==len) doubleSpace();
            T* temp=data+len-1;
            T* before_temp=data+len-2;
            T* target=pos.pt;

            this->push_back(*temp);
            while(temp!=target&&temp!=data){
                *temp=*before_temp;
                temp--;
                before_temp--;
            }
            *temp=value;
            return iterator(temp, this);
        }
        /**
         * inserts value at index ind.
         * after inserting, this->at(ind) == value
         * returns an iterator pointing to the inserted value.
         * throw index_out_of_bound if ind > size (in this situation ind can be size because after inserting the size will increase 1.)
         */
        iterator insert(const size_t &ind, const T &value) {
            if(ind>len) throw index_out_of_bound();
            if(capacity==len) doubleSpace();
            T* temp=data+len-1;
            T* before_temp=data+len-2;
            T* target=data+ind;
            this->push_back(*temp);
            temp--;
            while(temp!=target&&temp!=data){
                *temp=*before_temp;
                temp--;
                before_temp--;
            }
            *temp=value;
            return iterator(temp, this);
        }
        /**
         * removes the element at pos.
         * return an iterator pointing to the following element.
         * If the iterator pos refers the last element, the end() iterator is returned.
         */
        iterator erase(iterator pos) {
            T* temp=pos.pt;
            T* next=temp+1;
            while (next!=data+len){
                *temp=*next;
                temp++;
                next++;
            }
            this->pop_back();
            return iterator(pos.pt,this);
        }
        /**
         * removes the element with index ind.
         * return an iterator pointing to the following element.
         * throw index_out_of_bound if ind >= size
         */
        iterator erase(const size_t &ind) {
            if(ind>=len) throw index_out_of_bound();
            T* temp=data+ind;
            T* next=temp+1;
            while (next!=data+len){
                *temp=*next;
                temp++;
                next++;
            }
            this->pop_back();
            return iterator(data+ind,this);
        }
        /**
         * adds an element to the end.
         */
        void push_back(const T &value) {
            if(capacity==len) doubleSpace();
            new(data+len) T(value);
            len++;
        }
        /**
         * remove the last element from the end.
         * throw container_is_empty if size() == 0
         */
        void pop_back() {
            if(len==0) throw container_is_empty();
            len--;
            (data+len)->~T();
            //if(len<capacity/3&&len!=0) cutSpace();
        }
    };

    template <class T>
    T* upper_bound(T* first,T* last, T key) {
        if(first==last)return first;
        last--;
        if(key>=*last)return last+1;
        while (first < last) {
            T* mid = first + (last - first) / 2;
            if (key < *mid) {
                last = mid;
            } else {
                first = mid + 1;
            }
        }
        return first;
    }

    template <class T>
    T* lower_bound(T *first,T *last, T key) {
        if(first==last)return first;
        last--;
        if(key>*last)return last+1;
        while (first < last) {
            T* mid = first + (last - first) / 2;
            if (*mid < key) {
                first = mid + 1;
            } else {
                last = mid;
            }
        }
        return first;
    }

    template<class key,class value>
    class BPT;

    template<class key,class value>
    class Node{
    public:
        static const int size=4000/(sizeof(key)+ sizeof(value)+ sizeof(int));
        int Node_ID;
        int father;
        int len;
        int son[size]={};
        struct s{
            key k;
            value v;
        };
        s d[size]={};
        bool is_father_of_block;
        friend class BPT<key,value>;
    public:
        Node(){
            father=0;
            len=0;
            is_father_of_block=true;
        };
    };
    template<class key,class value>
    class Block{
        static const int size=4000/(sizeof(key)+ sizeof(value));
        int Block_ID;
        int father;
        int len;
        struct s{
            key k;
            value v;
        };
        s d[size]={};
        int next;
        friend class BPT<key,value>;
    public:
        Block(){
            father=0;
            len=0;
            next=-1;
        };
    };
    template<class key,class value>
    class BPT{
        typedef Node<key,value> node_type;
        typedef Block<key,value> block_type;
        const int end_pos = -1;
        int node_number=0;
        int block_number=0;
        std::string node_file_name;
        std::fstream node_data;
        std::string block_file_name;
        std::fstream block_data;
        node_type root;
        struct s{
            key k;
            value d;
            s(){};
            s(key k_,value v_):k(k_),d(v_){};
        };
    public:
        void read_node(int index,node_type& target){
            node_data.seekg(index * sizeof(node_type));
            node_data.read(reinterpret_cast<char*>(& target), sizeof(node_type));
        }
        void write_node(int index,node_type& target){
            node_data.seekp(index * sizeof(node_type));
            node_data.write(reinterpret_cast<char*>(& target), sizeof(node_type));
        }
        void read_block(int index,block_type& target){
            block_data.seekg(index * sizeof(block_type));
            block_data.read(reinterpret_cast<char*>(& target), sizeof(block_type));
        }
        void write_block(int index,block_type& target){
            block_data.seekp(index * sizeof(block_type));
            block_data.write(reinterpret_cast<char*>(& target), sizeof(node_type));
        }
        void calculate_node_and_block_amount_by_dfs(node_type now_node,int &n_a,int &b_a){
            int node_ans=0,block_ans=0;
            if(now_node.is_father_of_block) {
                ++node_ans;
                ++block_ans;
            }else{
                node_type nxt_node;
                for(int i=0;i<now_node.len;++i){
                    read_node(now_node.son[i],nxt_node);
                    calculate_node_and_block_amount_by_dfs(nxt_node,node_ans,block_ans);
                }
            }
            n_a+=node_ans;
            b_a+=block_ans;
        };
        BPT(const std::string &node_name="nodes",const std::string &block_name="blocks"){
            node_file_name=node_name;
            block_file_name=block_name;
            node_data.open(node_file_name);
            if(!node_data){
                node_data.open(node_file_name,std::ios::out);
                node_data.close();
                node_data.open(node_file_name);
                block_data.open(block_file_name,std::ios::out);
                block_data.close();
                block_data.open(block_file_name);
                ++node_number;
                root.Node_ID=node_number;
                root.len=1;
                block_type first_block;
                first_block.next=end_pos;
                ++block_number;
                first_block.Block_ID=block_number;
                root.father=-1;
                root.son[0]=1;
                first_block.len=0;
                write_node(0,root);
                write_block(0,first_block);
            }else{
                //dfs
                block_data.open(block_file_name);
                node_type now_node;
                block_type now_block;
                int node_amount=0,block_amount=0;
                calculate_node_and_block_amount_by_dfs(root,node_amount,block_amount);
                node_number=node_amount;
                block_number=block_amount;
                read_node(0,root);
            }
        };
        int find(s target,block_type& loc){

        }
        void merge_node(){

        };
        void merge_block(){

        };
        void split_node();
        void split_block();
        void node_insert();
        void node_erase();
        void insert(key k_,value v_){
            //第一个元素时特判
        };

        void erase();
        vector<s> dis();
    };


}
