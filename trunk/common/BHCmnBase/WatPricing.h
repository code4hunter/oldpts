//---------------------------------------------------------------------------

#ifndef UWATPRICINGH
#define UWATPRICINGH
//---------------------------------------------------------------------------
namespace TWatPricing
{
        double option_price(const double& S,       // spot (underlying) price   股票价格
                                               const double& K,       // strike (exercise) price,  行权价格
                                               const double& r,       // interest rate             无风险利率
                                               const double& sigma,   // volatility                波动率
                                               const double& time,   // time to maturity           到期期限
                                               char exemode,     //行权方式 '0'---若为欧式行权，'1'---为美式行权
                                               char type,        //权证类型  '0'--若为认购权证，'1'---为认沽权证
                                               short model=0);      //模型选择0--black_scholes

        double option_ivol(const double& S,       // spot (underlying) price   股票价格
                                               const double& K,       // strike (exercise) price,  行权价格
                                               const double& r,       // interest rate             无风险利率
                                               const double& time,   // time to maturity           到期期限
                                               const double& option_price, //期权的市场价格
                                               char exemode,     //行权方式'0'---若为欧式行权，'1'---为美式行权
                                               char type,        //权证类型   '0'--若为认购权证，'1'---为认沽权证
                                               short model=0);      //模型选择0--black_scholes

        bool option_params(const double& S,       // spot (underlying) price   股票价格
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
                                               double *theta);

        ///具体函数原型
        double n(const double& z);// normal distribution function  正态分布的密度函数
        double N(const double& z);//cumulative probability of univariate normal正态分布的累积概率函数
        double N1(const double& d);//cumulative probability of univariate normal  正态分布的累积概率函数

        //3、black_scholes 看涨期权 定价
        double option_price_european_call_black_scholes (
                                                const double& S,       // spot (underlying) price   股票价格
                                               const double& K,       // strike (exercise) price,  行权价格
                                               const double& r,       // interest rate             无风险利率
                                               const double& sigma,   // volatility                波动率
                                               const double& time);   // time to maturity           到期期限
        //4、black_scholes 看跌期权 定价
        double option_price_european_put_black_scholes (
                                                   const double& S,       // spot (underlying) price   股票价格
                                               const double& K,       // strike (exercise) price,  行权价格
                                               const double& r,       // interest rate             无风险利率
                                               const double& sigma,   // volatility                波动率
                                               const double& time);   // time to maturity           到期期限
        //5、Black scholes 欧式 看涨 期权的 隐含波动率计算
        double option_ivol_european_call_black_scholes(
                                                   const double& S,  //股票价格
                                               const double& K,  //执行价格
                                               const double& r,  //无风险利率
                                               const double& time,//到期时间
                                               const double& option_price); //期权的市场价格)
        //6、Black scholes 欧式 看跌 期权的 隐含波动率计算
        double option_ivol_european_put_black_scholes(
                                                   const double& S,  //股票价格
                                               const double& K,  //执行价格
                                               const double& r,  //无风险利率
                                               const double& time,//到期时间
                                               const double& option_price); //期权的市场价格)
        //7、Black scholes 欧式 看涨 期权的 delta计算

        double option_delta_european_call_black_scholes(const double& S,     // spot price
                                                     const double& K,     // Strike (exercise) price,
                                                     const double& r,     // interest rate
                                                     const double& sigma, // volatility
                                                     const double& time);  // time to maturity
        //8、Black scholes 欧式 看跌 期权的 delta计算

        double option_delta_european_put_black_scholes(const double& S, // spot price
                                                    const double& k, // Strike (exercise) price,
                                                    const double& r,  // interest rate
                                                    const double& sigma, // volatility
                                                    const double& time);// time to maturity
        //9、Black scholes 欧式 看涨 期权的 gamma计算

        double option_gamma_european_call_black_scholes(const double& S,     // spot price
                                                     const double& K,     // Strike (exercise) price,
                                                     const double& r,     // interest rate
                                                     const double& sigma, // volatility
                                                     const double& time);  // time to maturity
        //10、Black scholes 欧式 看跌 期权的 gamma计算
        double option_gamma_european_put_black_scholes(const double& S, // spot price
                                                    const double& k, // Strike (exercise) price,
                                                    const double& r,  // interest rate
                                                    const double& sigma, // volatility
                                                    const double& time);// time to maturity

        //11、Black scholes 欧式 看涨 期权的 vega计算

        double option_vega_european_call_black_scholes(const double& S,     // spot price
                                                     const double& K,     // Strike (exercise) price,
                                                     const double& r,     // interest rate
                                                     const double& sigma, // volatility
                                                     const double& time);  // time to maturity
        //12、Black scholes 欧式 看跌 期权的 vega计算
        double option_vega_european_put_black_scholes(const double& S, // spot price
                                                    const double& k, // Strike (exercise) price,
                                                    const double& r,  // interest rate
                                                    const double& sigma, // volatility
                                                    const double& time);// time to maturity
        //13、Black scholes 欧式 看涨 期权的 rho计算
        double option_rho_european_call_black_scholes(const double& S,     // spot price
                                                     const double& K,     // Strike (exercise) price,
                                                     const double& r,     // interest rate
                                                     const double& sigma, // volatility
                                                     const double& time);  // time to maturity
        //14、Black scholes 欧式 看跌 期权的 rho计算
        double option_rho_european_put_black_scholes(const double& S, // spot price
                                                    const double& k, // Strike (exercise) price,
                                                    const double& r,  // interest rate
                                                    const double& sigma, // volatility
                                                    const double& time);// time to maturity

        //15、Black scholes 欧式 看涨 期权的 theta计算

        double option_theta_european_call_black_scholes(const double& S,     // spot price
                                                     const double& K,     // Strike (exercise) price,
                                                     const double& r,     // interest rate
                                                     const double& sigma, // volatility
                                                     const double& time);  // time to maturity

        //16、Black scholes 欧式 看跌 期权的 theta计算
        double option_theta_european_put_black_scholes(const double& S, // spot price
                                                    const double& k, // Strike (exercise) price,
                                                    const double& r,  // interest rate
                                                    const double& sigma, // volatility
                                                    const double& time);// time to maturity 
};
//---------------------------------------------------------------------------
#endif
