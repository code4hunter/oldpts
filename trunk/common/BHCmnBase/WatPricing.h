//---------------------------------------------------------------------------

#ifndef UWATPRICINGH
#define UWATPRICINGH
//---------------------------------------------------------------------------
namespace TWatPricing
{
        double option_price(const double& S,       // spot (underlying) price   ��Ʊ�۸�
                                               const double& K,       // strike (exercise) price,  ��Ȩ�۸�
                                               const double& r,       // interest rate             �޷�������
                                               const double& sigma,   // volatility                ������
                                               const double& time,   // time to maturity           ��������
                                               char exemode,     //��Ȩ��ʽ '0'---��Ϊŷʽ��Ȩ��'1'---Ϊ��ʽ��Ȩ
                                               char type,        //Ȩ֤����  '0'--��Ϊ�Ϲ�Ȩ֤��'1'---Ϊ�Ϲ�Ȩ֤
                                               short model=0);      //ģ��ѡ��0--black_scholes

        double option_ivol(const double& S,       // spot (underlying) price   ��Ʊ�۸�
                                               const double& K,       // strike (exercise) price,  ��Ȩ�۸�
                                               const double& r,       // interest rate             �޷�������
                                               const double& time,   // time to maturity           ��������
                                               const double& option_price, //��Ȩ���г��۸�
                                               char exemode,     //��Ȩ��ʽ'0'---��Ϊŷʽ��Ȩ��'1'---Ϊ��ʽ��Ȩ
                                               char type,        //Ȩ֤����   '0'--��Ϊ�Ϲ�Ȩ֤��'1'---Ϊ�Ϲ�Ȩ֤
                                               short model=0);      //ģ��ѡ��0--black_scholes

        bool option_params(const double& S,       // spot (underlying) price   ��Ʊ�۸�
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
                                               double *theta);

        ///���庯��ԭ��
        double n(const double& z);// normal distribution function  ��̬�ֲ����ܶȺ���
        double N(const double& z);//cumulative probability of univariate normal��̬�ֲ����ۻ����ʺ���
        double N1(const double& d);//cumulative probability of univariate normal  ��̬�ֲ����ۻ����ʺ���

        //3��black_scholes ������Ȩ ����
        double option_price_european_call_black_scholes (
                                                const double& S,       // spot (underlying) price   ��Ʊ�۸�
                                               const double& K,       // strike (exercise) price,  ��Ȩ�۸�
                                               const double& r,       // interest rate             �޷�������
                                               const double& sigma,   // volatility                ������
                                               const double& time);   // time to maturity           ��������
        //4��black_scholes ������Ȩ ����
        double option_price_european_put_black_scholes (
                                                   const double& S,       // spot (underlying) price   ��Ʊ�۸�
                                               const double& K,       // strike (exercise) price,  ��Ȩ�۸�
                                               const double& r,       // interest rate             �޷�������
                                               const double& sigma,   // volatility                ������
                                               const double& time);   // time to maturity           ��������
        //5��Black scholes ŷʽ ���� ��Ȩ�� ���������ʼ���
        double option_ivol_european_call_black_scholes(
                                                   const double& S,  //��Ʊ�۸�
                                               const double& K,  //ִ�м۸�
                                               const double& r,  //�޷�������
                                               const double& time,//����ʱ��
                                               const double& option_price); //��Ȩ���г��۸�)
        //6��Black scholes ŷʽ ���� ��Ȩ�� ���������ʼ���
        double option_ivol_european_put_black_scholes(
                                                   const double& S,  //��Ʊ�۸�
                                               const double& K,  //ִ�м۸�
                                               const double& r,  //�޷�������
                                               const double& time,//����ʱ��
                                               const double& option_price); //��Ȩ���г��۸�)
        //7��Black scholes ŷʽ ���� ��Ȩ�� delta����

        double option_delta_european_call_black_scholes(const double& S,     // spot price
                                                     const double& K,     // Strike (exercise) price,
                                                     const double& r,     // interest rate
                                                     const double& sigma, // volatility
                                                     const double& time);  // time to maturity
        //8��Black scholes ŷʽ ���� ��Ȩ�� delta����

        double option_delta_european_put_black_scholes(const double& S, // spot price
                                                    const double& k, // Strike (exercise) price,
                                                    const double& r,  // interest rate
                                                    const double& sigma, // volatility
                                                    const double& time);// time to maturity
        //9��Black scholes ŷʽ ���� ��Ȩ�� gamma����

        double option_gamma_european_call_black_scholes(const double& S,     // spot price
                                                     const double& K,     // Strike (exercise) price,
                                                     const double& r,     // interest rate
                                                     const double& sigma, // volatility
                                                     const double& time);  // time to maturity
        //10��Black scholes ŷʽ ���� ��Ȩ�� gamma����
        double option_gamma_european_put_black_scholes(const double& S, // spot price
                                                    const double& k, // Strike (exercise) price,
                                                    const double& r,  // interest rate
                                                    const double& sigma, // volatility
                                                    const double& time);// time to maturity

        //11��Black scholes ŷʽ ���� ��Ȩ�� vega����

        double option_vega_european_call_black_scholes(const double& S,     // spot price
                                                     const double& K,     // Strike (exercise) price,
                                                     const double& r,     // interest rate
                                                     const double& sigma, // volatility
                                                     const double& time);  // time to maturity
        //12��Black scholes ŷʽ ���� ��Ȩ�� vega����
        double option_vega_european_put_black_scholes(const double& S, // spot price
                                                    const double& k, // Strike (exercise) price,
                                                    const double& r,  // interest rate
                                                    const double& sigma, // volatility
                                                    const double& time);// time to maturity
        //13��Black scholes ŷʽ ���� ��Ȩ�� rho����
        double option_rho_european_call_black_scholes(const double& S,     // spot price
                                                     const double& K,     // Strike (exercise) price,
                                                     const double& r,     // interest rate
                                                     const double& sigma, // volatility
                                                     const double& time);  // time to maturity
        //14��Black scholes ŷʽ ���� ��Ȩ�� rho����
        double option_rho_european_put_black_scholes(const double& S, // spot price
                                                    const double& k, // Strike (exercise) price,
                                                    const double& r,  // interest rate
                                                    const double& sigma, // volatility
                                                    const double& time);// time to maturity

        //15��Black scholes ŷʽ ���� ��Ȩ�� theta����

        double option_theta_european_call_black_scholes(const double& S,     // spot price
                                                     const double& K,     // Strike (exercise) price,
                                                     const double& r,     // interest rate
                                                     const double& sigma, // volatility
                                                     const double& time);  // time to maturity

        //16��Black scholes ŷʽ ���� ��Ȩ�� theta����
        double option_theta_european_put_black_scholes(const double& S, // spot price
                                                    const double& k, // Strike (exercise) price,
                                                    const double& r,  // interest rate
                                                    const double& sigma, // volatility
                                                    const double& time);// time to maturity 
};
//---------------------------------------------------------------------------
#endif
