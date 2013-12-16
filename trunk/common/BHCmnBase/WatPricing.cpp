//---------------------------------------------------------------------------

#pragma hdrstop

#include "WatPricing.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
#include <math.h>
#ifndef PI 
#define PI 3.141592653589793238462643
#endif

//1��	��̬�ֲ����ܶȺ���
//////////////////////////////////////////////////////
double TWatPricing::n(const double& z)
 // normal distribution function  ��̬�ֲ����ܶȺ���
{   
    return (1.0/sqrt(2.0*PI))*exp(-0.5*z*z);
};

//2����̬�ֲ����ۻ����ʺ���

double TWatPricing::N(const double& z)
 //cumulative probability of univariate normal��̬�ֲ����ۻ����ʺ���
{
    if (z >  6.0) { return 1.0; }; // this guards against overflow 
    if (z < -6.0) { return 0.0; };

    double b1 =  0.31938153; 
    double b2 = -0.356563782; 
    double b3 =  1.781477937;
    double b4 = -1.821255978;
    double b5 =  1.330274429; 
    double p  =  0.2316419; 
    double c2 =  0.3989423; 

    double a=fabs(z); 
    double t = 1.0/(1.0+a*p); 
    double b = c2*exp((-z)*(z/2.0)); 
    double n = ((((b5*t+b4)*t+b3)*t+b2)*t+b1)*t; 
    n = 1.0-b*n; 
    if ( z < 0.0 ) n = 1.0 - n; 
    return n; 
};


double TWatPricing::N1(const double& d)
//cumulative probability of univariate normal  ��̬�ֲ����ۻ����ʺ���
{ 	 
	double a1 = 0.319381530; 	 
	double a2 = -0.356563782; 	 
	double a3 = 1.781477937; 	 
	double a4 = -1.821255978; 	 
	double a5 = 1.330274429; 	 
	double gamma = 0.2316419; 	 
	double k1 = 1/(1 + gamma*d); 	 
	double k2 = 1/(1 -gamma*d); 	 
	double normalprime = (1/(sqrt(2*PI)))*exp(-d*d/2); 	 
	double value = 0.0; 	 
	//double h = 0.0; 	 
	if (d >= 0) 	 
    	        value = 1- normalprime*(a1*k1 + a2*pow(k1,2) + a3*pow(k1,3) + a4*pow(k1,4) + a5*pow(k1,5)); 	 
	else 	 
	    value = normalprime*(a1*k2 + a2*pow(k2,2) + a3*pow(k2,3) + a4*pow(k2,4) + a5*pow(k2,5)); 	 
	return value; 	 
}



//3��black_scholes ������Ȩ ���� 
double TWatPricing::option_price_european_call_black_scholes (
					   const double& S,       // spot (underlying) price   ��Ʊ�۸�
				       const double& K,       // strike (exercise) price,  ��Ȩ�۸�
				       const double& r,       // interest rate             �޷�������
				       const double& sigma,   // volatility                ������
				       const double& time)   // time to maturity           ��������
{  // time to maturity 
    double time_sqrt = sqrt(time);
    double d1 = (log(S/K)+r*time)/(sigma*time_sqrt)+0.5*sigma*time_sqrt; 
    double d2 = d1-(sigma*time_sqrt);
    return S*N(d1) - K*exp(-r*time)*N(d2);
};


//4��black_scholes ������Ȩ ����
double TWatPricing::option_price_european_put_black_scholes (
					   const double& S,       // spot (underlying) price   ��Ʊ�۸�
				       const double& K,       // strike (exercise) price,  ��Ȩ�۸�
				       const double& r,       // interest rate             �޷�������
				       const double& sigma,   // volatility                ������
				       const double& time)   // time to maturity           ��������
{  // time to maturity 
    double time_sqrt = sqrt(time);
    double d1 = (log(S/K)+r*time)/(sigma*time_sqrt)+0.5*sigma*time_sqrt; 
    double d2 = d1-(sigma*time_sqrt);
    return K*exp(-r*time)*N(-d2) - S*N(-d1);
};


//5��Black scholes ŷʽ ���� ��Ȩ�� ���������ʼ���
double TWatPricing::option_ivol_european_call_black_scholes(
									 const double& S,  //��Ʊ�۸�
								     const double& K,  //ִ�м۸�
								     const double& r,  //�޷�������
								     const double& time,//����ʱ��
								     const double& option_price) //��Ȩ���г��۸�)
{
    double price;
    const double ACCURACY = 1.0e-5; // make this smaller for higher accuracy
    double sigma_low=0;
    double sigma_high=2;
	
    while(sigma_high-sigma_low>ACCURACY)
	{
		price=option_price_european_call_black_scholes(S,K,r,(sigma_high+sigma_low)/2,time);
		if (price>option_price)
         sigma_high = (sigma_high+sigma_low) / 2;
         else
	     sigma_low = (sigma_high+sigma_low) / 2;
	};


   return (sigma_high+sigma_low)/2;

};


//6��Black scholes ŷʽ ���� ��Ȩ�� ���������ʼ���
double TWatPricing::option_ivol_european_put_black_scholes(
									 const double& S,  //��Ʊ�۸�
								     const double& K,  //ִ�м۸�
								     const double& r,  //�޷�������
								     const double& time,//����ʱ��
								     const double& option_price) //��Ȩ���г��۸�)
{
    double price;
    const double ACCURACY = 1.0e-5; // make this smaller for higher accuracy
    double sigma_low=0;
    double sigma_high=2;
	
    while(sigma_high-sigma_low>ACCURACY)
	{
		price=option_price_european_put_black_scholes(S,K,r,(sigma_high+sigma_low)/2,time);
		if (price>option_price)
         sigma_high = (sigma_high+sigma_low) / 2;
         else
	     sigma_low = (sigma_high+sigma_low) / 2;
	};


   return (sigma_high+sigma_low)/2;

};


//7��Black scholes ŷʽ ���� ��Ȩ�� delta����

double TWatPricing::option_delta_european_call_black_scholes(const double& S,     // spot price
					     const double& K,     // Strike (exercise) price,
					     const double& r,     // interest rate
					     const double& sigma, // volatility
					     const double& time)  // time to maturity
{  
    double time_sqrt = sqrt(time);
    double d1 = (log(S/K)+r*time)/(sigma*time_sqrt) + 0.5*sigma*time_sqrt; 
    double delta = N(d1);
    return delta;
};


//8��Black scholes ŷʽ ���� ��Ȩ�� delta����

double TWatPricing::option_delta_european_put_black_scholes(const double& S, // spot price
					    const double& k, // Strike (exercise) price,
					    const double& r,  // interest rate
					    const double& sigma, // volatility
					    const double& time)// time to maturity
 {
    double time_sqrt = sqrt(time);
    double d1 = (log(S/k)+r*time)/(sigma*time_sqrt) + 0.5*sigma*time_sqrt; 
    double delta = -N(-d1);
    return delta;
}



//9��Black scholes ŷʽ ���� ��Ȩ�� gamma����

double TWatPricing::option_gamma_european_call_black_scholes(const double& S,     // spot price
					     const double& K,     // Strike (exercise) price,
					     const double& r,     // interest rate
					     const double& sigma, // volatility
					     const double& time)  // time to maturity
{  
    double time_sqrt = sqrt(time);
    double d1 = (log(S/K)+r*time)/(sigma*time_sqrt) + 0.5*sigma*time_sqrt; 
    double gamma = n(d1)/(S*sigma*time_sqrt);
    return gamma;
};


//10��Black scholes ŷʽ ���� ��Ȩ�� gamma����
double TWatPricing::option_gamma_european_put_black_scholes(const double& S, // spot price
					    const double& k, // Strike (exercise) price,
					    const double& r,  // interest rate
					    const double& sigma, // volatility
					    const double& time)// time to maturity
 {
    double time_sqrt = sqrt(time);
    double d1 = (log(S/k)+r*time)/(sigma*time_sqrt) + 0.5*sigma*time_sqrt; 
    double gamma =n(d1)/(S*sigma*time_sqrt);
    return gamma;
}




//11��Black scholes ŷʽ ���� ��Ȩ�� vega����

double TWatPricing::option_vega_european_call_black_scholes(const double& S,     // spot price
					     const double& K,     // Strike (exercise) price,
					     const double& r,     // interest rate
					     const double& sigma, // volatility
					     const double& time)  // time to maturity
{  
    double time_sqrt = sqrt(time);
    double d1 = (log(S/K)+r*time)/(sigma*time_sqrt) + 0.5*sigma*time_sqrt; 
    double vega = S*time_sqrt*n(d1);
    return vega;
};


//12��Black scholes ŷʽ ���� ��Ȩ�� vega����
double TWatPricing::option_vega_european_put_black_scholes(const double& S, // spot price
					    const double& k, // Strike (exercise) price,
					    const double& r,  // interest rate
					    const double& sigma, // volatility
					    const double& time)// time to maturity
 {
    double time_sqrt = sqrt(time);
    double d1 = (log(S/k)+r*time)/(sigma*time_sqrt) + 0.5*sigma*time_sqrt; 
    double vega = S*time_sqrt*n(d1);
    return vega;
}



//13��Black scholes ŷʽ ���� ��Ȩ�� rho����

double TWatPricing::option_rho_european_call_black_scholes(const double& S,     // spot price
					     const double& K,     // Strike (exercise) price,
					     const double& r,     // interest rate
					     const double& sigma, // volatility
					     const double& time)  // time to maturity
{  
    double time_sqrt = sqrt(time);
    double d1 = (log(S/K)+r*time)/(sigma*time_sqrt) + 0.5*sigma*time_sqrt; 
	double d2 = d1-(sigma*time_sqrt);
    double rho =time*K*exp(-r*time)*N(d2);
    return rho;
};


//14��Black scholes ŷʽ ���� ��Ȩ�� rho����
double TWatPricing::option_rho_european_put_black_scholes(const double& S, // spot price
					    const double& k, // Strike (exercise) price,
					    const double& r,  // interest rate
					    const double& sigma, // volatility
					    const double& time)// time to maturity
 {
    double time_sqrt = sqrt(time);
    double d1 = (log(S/k)+r*time)/(sigma*time_sqrt) + 0.5*sigma*time_sqrt; 
	double d2 = d1-(sigma*time_sqrt);
    double rho =-time*k*exp(-r*time)*N(-d2);
    return rho;
}

//15��Black scholes ŷʽ ���� ��Ȩ�� theta����

double TWatPricing::option_theta_european_call_black_scholes(const double& S,     // spot price
					     const double& K,     // Strike (exercise) price,
					     const double& r,     // interest rate
					     const double& sigma, // volatility
					     const double& time)  // time to maturity
{  
    double time_sqrt = sqrt(time);
    double d1 = (log(S/K)+r*time)/(sigma*time_sqrt) + 0.5*sigma*time_sqrt; 
	double d2 = d1-(sigma*time_sqrt);
    double rho =-S*sigma*n(d1)/(2*time_sqrt)-K*r*exp(-r*time)*N(d2);
    return rho;
};


//16��Black scholes ŷʽ ���� ��Ȩ�� theta����
double TWatPricing::option_theta_european_put_black_scholes(const double& S, // spot price
					    const double& k, // Strike (exercise) price,
					    const double& r,  // interest rate
					    const double& sigma, // volatility
					    const double& time)// time to maturity
 {
    double time_sqrt = sqrt(time);
    double d1 = (log(S/k)+r*time)/(sigma*time_sqrt) + 0.5*sigma*time_sqrt; 
	double d2 = d1-(sigma*time_sqrt);
    double rho =-S*sigma*n(d1)/(2*time_sqrt)+k*r*exp(-r*time)*N(-d2);
    return rho;
}


//---------------------------------------------------------------------------
double CheckPrice(double StkPrice)
{
  if(StkPrice > 0.01)
    return true;
  else
    return false;
}
//---------------------------------------------------------------------------
double TWatPricing::option_price(const double& S,       // spot (underlying) price   ��Ʊ�۸�
                     const double& K,       // strike (exercise) price,  ��Ȩ�۸�
                     const double& r,       // interest rate             �޷�������
                     const double& sigma,   // volatility                ������
                     const double& time,   // time to maturity           ��������
                     char exemode,     //��Ȩ��ʽ '0'---��Ϊŷʽ��Ȩ��'1'---Ϊ��ʽ��Ȩ
                     char type,        //Ȩ֤����  '0'--��Ϊ�Ϲ�Ȩ֤��'1'---Ϊ�Ϲ�Ȩ֤
                     short model)      //ģ��ѡ��0--black_scholes
{
  if(!CheckPrice(S))
    return false;

  try
  {
    if(model == 0)//ģ��ѡ��0--black_scholes
    {
      if(exemode == '0')//'0'---��Ϊŷʽ��Ȩ��'1'---Ϊ��ʽ��Ȩ
      {
        if(type == '0')//Ȩ֤����  '0'--��Ϊ�Ϲ�Ȩ֤��'1'---Ϊ�Ϲ�Ȩ֤
          return option_price_european_call_black_scholes(S, K, r, sigma, time);
        else if(type == '1')                                    
          return option_price_european_put_black_scholes(S, K, r, sigma, time);
      }
    }
  }
  catch(...)
  {
    return 0;
  }

  return 0;
}

double TWatPricing::option_ivol(const double& S,       // spot (underlying) price   ��Ʊ�۸�
                                       const double& K,       // strike (exercise) price,  ��Ȩ�۸�
                                       const double& r,       // interest rate             �޷�������
                                       const double& time,   // time to maturity           ��������
                                       const double& option_price, //��Ȩ���г��۸�
                                       char exemode,     //��Ȩ��ʽ '0'---��Ϊŷʽ��Ȩ��'1'---Ϊ��ʽ��Ȩ
                                       char type,        //Ȩ֤����  '0'--��Ϊ�Ϲ�Ȩ֤��'1'---Ϊ�Ϲ�Ȩ֤
                                       short model)      //ģ��ѡ��0--black_scholes
{
  if(!CheckPrice(S))
    return false;

  try
  {
    if(model == 0)//ģ��ѡ��0--black_scholes
    {
      if(exemode == '0')//��Ȩ��ʽ '0'---��Ϊŷʽ��Ȩ��'1'---Ϊ��ʽ��Ȩ
      {
        if(type == '0')//Ȩ֤����  '0'--��Ϊ�Ϲ�Ȩ֤��'1'---Ϊ�Ϲ�Ȩ֤
          return option_ivol_european_call_black_scholes(S, K, r, time, option_price);
        else if(type == '1')
          return option_ivol_european_put_black_scholes(S, K, r, time, option_price);
      }
    }
  }
  catch(...)
  {
    return 0;
  }

  return 0;
}

bool TWatPricing::option_params(const double& S,       // spot (underlying) price   ��Ʊ�۸�
                                       const double& K,       // strike (exercise) price,  ��Ȩ�۸�
                                       const double& r,       // interest rate             �޷�������
                                       const double& sigma,   // volatility                ������
                                       const double& time,   // time to maturity           ��������
                                       char exemode,     //��Ȩ��ʽ '0'---��Ϊŷʽ��Ȩ��'1'---Ϊ��ʽ��Ȩ
                                       char type,        //Ȩ֤����  '0'--��Ϊ�Ϲ�Ȩ֤��'1'---Ϊ�Ϲ�Ȩ֤
                                       short model,      //ģ��ѡ��0--black_scholes
                                       double *delta,
                                       double *gamma,
                                       double *vega,
                                       double *rho,
                                       double *theta)
{
  //Init
  if(delta != NULL)
    *delta = 0.0;

  if(gamma != NULL)
    *gamma = 0.0;

  if(vega != NULL)
    *vega = 0.0;

  if(rho != NULL)
    *rho = 0.0;

  if(theta != NULL)
    *theta = 0.0;

  if(!CheckPrice(S))
    return false;
                
  try
  {
    if(model == 0)//ģ��ѡ��0--black_scholes
    {
      if(exemode == '0')//��Ȩ��ʽ '0'---��Ϊŷʽ��Ȩ��'1'---Ϊ��ʽ��Ȩ
      {
        if(type == '0')//Ȩ֤����  '0'--��Ϊ�Ϲ�Ȩ֤��'1'---Ϊ�Ϲ�Ȩ֤
        {
          if(delta != NULL)
            *delta = option_delta_european_call_black_scholes(S, K, r, sigma, time);

          if(gamma != NULL)
            *gamma = option_gamma_european_call_black_scholes(S, K, r, sigma, time);

          if(vega != NULL)
            *vega = option_vega_european_call_black_scholes(S, K, r, sigma, time);

          if(rho != NULL)
            *rho = option_rho_european_call_black_scholes(S, K, r, sigma, time);

          if(theta != NULL)
            *theta = option_theta_european_call_black_scholes(S, K, r, sigma, time);
        
          return true;
        }
        else if(type == '1')
        {
          if(delta != NULL)
            *delta = option_delta_european_put_black_scholes(S, K, r, sigma, time);

          if(gamma != NULL)
            *gamma = option_gamma_european_put_black_scholes(S, K, r, sigma, time);

          if(vega != NULL)
            *vega = option_vega_european_put_black_scholes(S, K, r, sigma, time);

          if(rho != NULL)
            *rho = option_rho_european_put_black_scholes(S, K, r, sigma, time);

          if(theta != NULL)
            *theta = option_theta_european_put_black_scholes(S, K, r, sigma, time);
          
          return true;
        }
      }
    }
  }
  catch(...)
  {
    return false;
  }

  return false;
}
