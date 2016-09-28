//calc1是可以直接积分的部分，减少精度误差
double calc1(double x) {
    return a/4.0*x*x*x*x+b/3.0*x*x*x;
}
//f是除了直接积分部分的原函数
double f(double x)
{
    return c*x*log(x);//自定义函数
}
double simpson(double a,double b)
{
    double c=a+(b-a)/2;
    return (f(a)+4*f(c)+f(b))*(b-a)/6;
}
//递归过程，可以保存la,rb,和simpson的值，若la,rb未变
//则直接使用保存的simpson值不用再调用simpson函数，
//若改变则调用函数并保存修改后的值
//eps为自定义精度
double asr(double a,double b,double eps,double A)
{
    double c=a+(b-a)/2;
    double L=simpson(a,c),R=simpson(c,b);
    if(fabs(L+R-A)<=15*eps) return L+R+(L+R-A)/15.0;
    return asr(a,c,eps/2,L)+asr(c,b,eps/2,R);
}
//调用此函数
double asr_main(double a,double b,double eps)
{
    return asr(a,b,eps,simpson(a,b));
}