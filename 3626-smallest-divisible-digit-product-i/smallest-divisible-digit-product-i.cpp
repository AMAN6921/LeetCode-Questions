class Solution {
    public:
    int smallestNumber(int n, int t) {
        for(int i=n;i<100;i++){
            int pro = 1;
            if(i>0 && i<10){
                pro = i;
            }
            else if(i>=10 && i<100){
                pro = (i/10)*(i%10);
            }
            if(pro%t==0){
                return i;
            }
        }
        return 100;        
    }
};