#include "Parabola.h"
/**
  ******************************************************************************
  * @file    Parabola.c
  * @author IMTao
  * @version V1.0
  * @date 2019-12-9
  * @brief   ������ϼ���
  ******************************************************************************
  */

#define  angeTohudu(a)  radians(a)
#define  huduToangle(a) degrees(a)

bool Parabola_Matching(double angle_P, double d, double v0, double *result) {

	double  d2 = 0.118;//��������İ뾶
	double  h = 0;
	double g = 9.7833;//�㶫���������ٶ�

	//�Ƕȣ�������̧Ϊ������
	//double  angle_P = angeTohudu(90);//����ʱ����������ļн�
	double  angle_A = 0;//���ϵĲ����Ƕ�

	double  h1 = d * cos(angle_P);


	double ans = 0;
	double last_ans = 0;
	double jindu = 0.8;//��ǰ�Ĳ��Ծ���

	//�ж���Զ����Ƿ��н⡣
	//double L = cos(angle_P)*d;
	//double t = L / v0 * cos();


	double diffs = 0;
	double direction = 1;//Ĭ�����ӽǶȡ�

	int error = 0; //��������з�������
	do
	{
		angle_A += direction * PI / (180 * jindu);
		double angle_f = angle_A + angle_P;//��������ֱ����ļн�

		double L = sin(angle_P)*d;

		double vx = v0 * sin(angle_f);
		double vy = v0 * cos(angle_f);
		double t = L / vx;//����x �ܵ������ʱ��t
		double h2 = d2 * cos(angle_P) - d2 * cos(angle_f);//���������ӵĸ߶�
		h = h1 + h2;
		double Cal_h = vy * t + 0.5*g*t*t;

		//double zuo = -1 * v0*tan(angle_A - angle_P)*d*cos(angle_P) + (0.5*g*pow(d*cos(angle_P), 2) / (pow(v0*cos(angle_A - angle_P), 2)));
		//double you = d * sin(angle_P);

		last_ans = ans;
		ans = h - Cal_h;

		diffs = abs(ans) - abs(last_ans);
		if (diffs > 0 && last_ans != 0)//����ڼ���
		{
			direction *= -1;
			//cout << "����=" << direction << endl;
			jindu += 1;
			if (jindu > 20)
			{

				//cout << "���ȳ��ޣ�" << endl;
				printf("���ȳ��ޣ�\n");
				break;
			}
		}


		if (L < 0 || vx < 0 || angle_f>angeTohudu(180) || t < 0)
		{
			error = 1;//�����������
			/*cout << "�������" << endl
				<< vx << endl
				<< L << endl
				<< h1 << endl
				<< angle_A << endl
				<< h << endl;*/

			printf("vx=%.2f\nL=%.2f\nh1=%.2f\naA=%.2f\nh=%.2f\naP=%.2f\n", vx, L, h1, angle_A, h, huduToangle(angle_P));

			return false;
		}
	} while (abs(ans) >= 0.01 && error == 0);//���̵�����С����λ��

	//cout << ans << "==����=" << huduToangle(angle_A) << endl;
	*result = huduToangle(angle_A);
	return true;
}
