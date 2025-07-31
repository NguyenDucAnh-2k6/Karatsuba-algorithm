#include <bits/stdc++.h>

using namespace std;
// Tính tổng
string findSum(string str1, string str2) {
    if (str1.length() > str2.length()) {  //Quy ước từ đầu là str2 sẽ lớn hơn
        swap(str1,str2);
    }
    string str=""; //Kết quả
    int n1=str1.length();
    int n2=str2.length();
    //Đảo lại 2 xâu tính cho tiện
    reverse(str1.begin(), str1.end());
    reverse(str2.begin(), str2.end());
    int carry=0;
    for (int i=0; i<n1;i++) {
        int sum=(str1[i]-'0')+(str2[i]-'0')+carry;
        str.push_back(sum%10+'0');
        carry=sum/10;
    }
    //Xử lý phần còn lại của xâu dài
    for (int i=n1; i<n2;i++) {
        int sum=((str2[i]-'0')+carry);
        str.push_back(sum%10 + '0');
        carry=sum/10;
    }
    if (carry)  //Nếu vẫn còn đại lượng “nhớ”, xử lý rồi cho vào str
        str.push_back(carry+'0');
    reverse(str.begin(), str.end());  //quá trình tính toán đã tạo ra xâu kết quả ngược nên bây giờ phải đảo lại
    return str;
}
//Hàm hiệu
string findDiff(string str1, string str2) {
    string str="";
    int n1=str1.length();
    int n2=str2.length();
    reverse(str1.begin(),str1.end());
    reverse(str2.begin(), str2.end());
    int carry=0;  //”Nhớ”
    for (int i=0; i<n2;i++) {  //xét xâu nhỏ trước
        int diff=(str1[i]-'0')-(str2[i]-'0')-carry;
        if (diff<0) {
            carry=1;
            diff=diff+10;
        }
        else {
            carry=0;
        }
        str.push_back(diff+'0');
    }
    //Xử lý những chữ số còn lại của xâu dài
    for (int i=n2; i<n1;i++) {
        int ex_sub=(str1[i]-'0')-carry;
        if (ex_sub<0) {
            ex_sub=ex_sub+10;
            carry=1;
        }
        else carry=0;
        str.push_back(ex_sub+'0');
    }
    reverse(str.begin(), str.end());
    return str;
}
// Xóa bỏ các số “0” ở đầu xâu 
string removeLeadingZeros(string str) {
    int i = 0;
    while (i < str.size() && str[i] == '0') {
        ++i;
    }
    string result = str.substr(i);
    return result.empty() ? "0" : result;
}
//Hàm nhân bằng thuật chia để trị “Karatsuba”
string multiplyStrings(string A, string B) {
    if (A.length()>B.length()) swap(A,B);
    //Đảm bảo 2 xâu cùng độ dài bằng cách thêm ‘0’ vào đầu xâu nhỏ
    int n1=A.length();
    int n2=B.length();
    while (n1<n2) {
        A='0'+A;
        n1++;
    }
    //Trường hợp cơ sở
    if (n1==1) {
        int res=stoi(A)*stoi(B);  //stoi(string) chuyển string về số
        return to_string(res);   //to_string chuyển số về xâu
    }
    //đảm bảo n chẵn
    if (n1%2==1) {
        n1++;
        A="0"+A;
        B="0"+B;
    }
    //Xác định các xâu a,b,c,d
    string a,b,c,d;
    for (int i=0;i<n1/2;i++) {
        a+=A[i];
        b+=A[n1/2+i];
        c+=B[i];
        d+=B[n1/2+i];
    }
    //Xác định u,v,w
    string u=multiplyStrings(a,c);
    string v=multiplyStrings(b,d);
    string w=findDiff(multiplyStrings(findSum(a,b), findSum(c,d)),findSum(u,v));
    //u*10^n/2
    for (int i=0;i<n1; i++) {
        u=u+'0';
    }
    //v*10^n/2
    for (int i=0; i<n1/2;i++) {
        w=w+'0';
    }
    //Dựa vào công thức Karatsuba
    string ans=findSum(findSum(u,w), v);
    //Xóa bỏ ‘0’ ở đầu kết quả
    ans=removeLeadingZeros(ans);
    return ans;
}
int main()
{
    string A;
    string B;
    cin >> A;
    cin >> B;
   cout << multiplyStrings(A, B);
   return 0;
}
