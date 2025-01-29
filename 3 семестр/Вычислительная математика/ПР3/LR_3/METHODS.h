extern double F(double);
/******************************************************************/
/*           Function F (X) , zadavaemaya polzovatelem            */
/******************************************************************/

#ifdef __NEWTON
extern double F1(double);
/******************************************************************/
/*     Proizvodnaya function F (X) , zadavaemaya polzovatelem     */
/******************************************************************/
#endif

double Round (double X,double Delta);
/******************************************************************/
/*   Function Round (X,Delta) , prednaznachena dlya okrugleniya   */
/*                   X c tochnostyu Delta                         */
/******************************************************************/

double BISECT(double Left,double Right,double Eps,int &N);
/******************************************************************/
/* Function BISECT prednaznachenadlya resheniya uravneniya F(X)=0 */
/*    metodom deleniya otrezka popolam. Ispolzovany oboznacheniya:*/
/*      Left - levyi konets promezhutka                           */
/*      Right - pravyi konets promezhutka                         */
/*      Eps - pogreshnost vychisleniya kornya uravneniya;         */
/*      N - chislo iteratsiy                                      */
/******************************************************************/

double ITER(double X0,double Eps,int &N);
/******************************************************************/
/*    �㭪�� ITER �।�����祭� ��� �襭�� �ࠢ����� F(X)=X     */
/*      ��⮤�� ���⮩ ���樨. �ᯮ�짮���� ������祭��:       */
/*      X0 - ��砫쭮� �ਡ������� ����                          */
/*      Eps - ����譮��� ���᫥��� ���� �ࠢ�����;             */
/*      N - �᫮ ���権                                        */
/******************************************************************/

double HORDA(double Left,double Right,double Eps,int &N);
/******************************************************************/
/*    �㭪�� HORDA �।�����祭� ��� �襭�� �ࠢ����� F(x)=0    */
/*      ��⮤�� ��. �ᯮ�짮���� ������祭��:                   */
/*      Left - ���� ����� �஬���⪠                             */
/*      Right - �ࠢ� ����� �஬���⪠                           */
/*      Eps - ����譮��� ���᫥��� ���� �ࠢ�����;             */
/*      N - �᫮ ���権                                        */
/******************************************************************/

double NEWTON (double X,double Eps,int &N);
/******************************************************************/
/*  �㭪�� NEWTON �।�����祭� ��� �襭�� �ࠢ����� F(X)=0     */
/*        ��⮤�� ���⥫���. �ᯮ�짮���� ������祭��:          */
/*      X - ��砫쭮� �ਡ������� ����                           */
/*      Eps - ����譮��� ���᫥��� ���� �ࠢ�����;             */
/*      N - �᫮ ���権                                        */
/******************************************************************/

#include "methods.cpp"
