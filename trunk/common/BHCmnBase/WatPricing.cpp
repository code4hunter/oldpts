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

//1、	正态分布的密度函数
//////////////////////////////////////////////////////
double TWatPricing::n(const double& z)
 // normal distribution function  正态分布的密度函数
{   
    return (1.0/sqrt(2.0*PI))*exp(-0.5*z*z);
};

//2、正态分布的累积概率函数

double TWatPricing::N(const double& z)
 //cumulative probability of univariate normal正态分布的累积概率函数
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
//cumulative probability of univariate normal  正态分布的累积概率函数
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



//3、black_scholes 看涨期权 定价 
double TWatPricing::option_price_european_call_black_scholes (
					   const double& S,       // spot (underlying) price   股票价格
				       const double& K,       // strike (exercise) price,  行权价格
				       const double& r,       // interest rate             无风险利率
				       const double& sigma,   // volatility                波动率
				       const double& time)   // time to maturity           到期期限
{  // time to maturity 
    double time_sqrt = sqrt(time);
    double d1 = (log(S/K)+r*time)/(sigma*time_sqrt)+0.5*sigma*time_sqrt; 
    double d2 = d1-(sigma*time_sqrt);
    return S*N(d1) - K*exp(-r*time)*N(d2);
};


//4、black_scholes 看跌期权 定价
double TWatPricing::option_price_european_put_black_scholes (
					   const double& S,       // spot (underlying) price   股票价格
				       const double& K,       // strike (exercise) price,  行权价格
				       const double& r,       // interest rate             无风险利率
				       const double& sigma,   // volatility                波动率
				       const double& time)   // time to maturity           到期期限
{  // time to maturity 
    double time_sqrt = sqrt(time);
    double d1 = (log(S/K)+r*time)/(sigma*time_sqrt)+0.5*sigma*time_sqrt; 
    double d2 = d1-(sigma*time_sqrt);
    return K*exp(-r*time)*N(-d2) - S*N(-d1);
};


//5、Black scholes 欧式 看涨 期权的 隐含波动率计算
double TWatPricing::option_ivol_european_call_black_scholes(
									 const double& S,  //股票价格
								     const double& K,  //执行价格
								     const double& r,  //无风险利率
								     const double& time,//到期时间
								     const double& option_price) //期权的市场价格)
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


//6、Black scholes 欧式 看跌 期权的 隐含波动率计算
double TWatPricing::option_ivol_european_put_black_scholes(
									 const double& S,  //股票价格
								     const double& K,  //执行价格
								     const double& r,  //无风险利率
								     const double& time,//到期时间
								     const double& option_price) //期权的市场价格)
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


//7、Black scholes 欧式 看涨 期权的 delta计算

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


//8、Black scholes 欧式 看跌 期权的 delta计算

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



//9、Black scholes 欧式 看涨 期权的 gamma计算

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


//10、Black scholes 欧式 看跌 期权的 gamma计算
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




//11、Black scholes 欧式 看涨 期权的 vega计算

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


//12、Black scholes 欧式 看跌 期权的 vega计算
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



//13、Black scholes 欧式 看涨 期权的 rho计算

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


//14、Black scholes 欧式 看跌 期权的 rho计算
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

//15、Black scholes 欧式 看涨 期权的 theta计算

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


//16、Black scholes 欧式 看跌 期权的 theta计算
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
double TWatPricing::option_price(const double& S,       // spot (underlying) price   股票价格
                     const double& K,       // strike (exercise) price,  行权价格
                     const double& r,       // interest rate             无风险利率
                     const double& sigma,   // volatility                波动率
                     const double& time,   // time to maturity           到期期限
                     char exemode,     //行权方式 '0'---若为欧式行权，'1'---为美式行权
                     char type,        //权证类型  '0'--若为认购权证，'1'---为认沽权证
                     short model)      //模型选择0--black_scholes
{
  if(!CheckPrice(S))
    return false;

  try
  {
    if(model == 0)//模型选择0--black_scholes
    {
      if(exemode == '0')//'0'---若为欧式行权，'1'---为美式行权
      {
        if(type == '0')//权证类型  '0'--若为认购权证，'1'---为认沽权证
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

double TWatPricing::option_ivol(const double& S,       // spot (underlying) price   股票价格
                                       const double& K,       // strike (exercise) price,  行权价格
                                       const double& r,       // interest rate             无风险利率
                                       const double& time,   // time to maturity           到期期限
                                       const double& option_price, //期权的市场价格
                                       char exemode,     //行权方式 '0'---若为欧式行权，'1'---为美式行权
                                       char type,        //权证类型  '0'--若为认购权证，'1'---为认沽权证
                                       short model)      //模型选择0--black_scholes
{
  if(!CheckPrice(S))
    return false;

  try
  {
    if(model == 0)//模型选择0--black_scholes
    {
      if(exemode == '0')//行权方式 '0'---若为欧式行权，'1'---为美式行权
      {
        if(type == '0')//权证类型  '0'--若为认购权证，'1'---为认沽权证
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

bool TWatPricing::option_params(const double& S,       // spot (underlying) price   股票价格
                                       const double& K,       // strike (exercise) price,  行权价格
                                       const double& r,       // interest rate             无风险利率
                                       const double& sigma,   // volatility                波动率
                                       const double& time,   // time to maturity           到期期限
                                       char exemode,     //行权方式 '0'---若为欧式行权，'1'---为美式行权
                                       char type,        //权证类型  '0'--若为认购权证，'1'---为认沽权证
                                       short model,      //模型选择0--black_scholes
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
    if(model == 0)//模型选择0--black_scholes
    {
      if(exemode == '0')//行权方式 '0'---若为欧式行权，'1'---为美式行权
      {
        if(type == '0')//权证类型  '0'--若为认购权证，'1'---为认沽权证
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
