#define _CRT_SECURE_NO_WARNINGS
#include <math.h>
#include <time.h>
#include <time.h>
#include <string.h>
#include <windows.h>

#include "zzc_bp_net.h"
#include "SurfaceClassfiy.h"
#define In_Num 1216        //�����ڵ���
#define Out_Num 6          //�����ڵ���
#define Hidden_Num 100     //���ز�ڵ���


#define DEF_ERR2_THROLD 0.001    //��С�������

#define DEF_ETA 0.1   //����

#define DEF_SAMPLE_NUM 1200   //����������
#define DEF_ITE_NUM 500  //��������


//������������� 
void bp_random_seed(int seed)
{
	//printf("Random number generator seed: %d\n", seed);
	srand(seed);
}


//����-1.0��1.0֮���˫���������
double get_random()
{
	return (((double)rand() / (double)RAND_MAX)*2.0 - 1.0);
}


// �����ʼ��Ȩֵ
void bp_randomize_weights(double **w, int m, int n)
{
	int i, j;

	for (i = 0; i <= m; i++) {
		for (j = 0; j <= n; j++) {

			w[i][j] = get_random();
		
		}
	}
}

/***��ʼ��ȨֵΪ0 ***/
void bp_zero_weights(double **w, int m, int n)
{
	int i, j;

	for (i = 0; i <= m; i++) {
		for (j = 0; j <= n; j++) {
			w[i][j] = 0.0;
		}
	}
}

double* alloc_1d_double_buf(unsigned int m)
{
	double *buf = NULL;

	buf = new double[m];
	if (buf == NULL)
	{
		exit(1);
	}

	return buf;
}

double** alloc_2d_double_buf(unsigned int m, unsigned int n)
{

	unsigned int i;
	double **buf = NULL;
	double *head;
	buf = (double **)malloc(sizeof(double *)*m + m*n*sizeof(double));

	if (buf == NULL)
	{
		exit(1);
	}

	head = (double *)(buf + m);

	memset((void *)head, 0x00, sizeof(double)*m*n);
	for (i = 0; i < m; i++)
	{

		buf[i] = head + i*n;
	}

	return buf;

}

void free_alloc_buf(void *p)
{

	if (p == NULL)
	{
		return;
	}

	free((void *)p);

}


double squash(double x)
{
	return (1.0 / (1.0 + exp(-x)));
}

//initial bp params
int init_bp_core_params(bp_alg_core_params *core_params)
{

	if (core_params == NULL)
	{
		return -1;
	}

	core_params->size = sizeof(bp_alg_core_params);
	core_params->err2_thresh = DEF_ERR2_THROLD;
	core_params->eta = DEF_ETA;
	core_params->sample_num = DEF_SAMPLE_NUM;
	core_params->train_ite_num = DEF_ITE_NUM;

	core_params->p_inlayer = new bp_input_layer_params;// (sizeof(bp_input_layer_params));
	if (core_params->p_inlayer == NULL)
	{
		return -1;
	}
	core_params->p_inlayer->in_num = In_Num; //����ڵ㣬������Ŀ

	/*���ز��ʼ��*/
	core_params->p_hidlayer = new bp_hidden_layer_params;
	if (core_params->p_inlayer == NULL)
	{
		return -1;
	}
	core_params->p_hidlayer->hid_num = Hidden_Num;//����ڵ���Ŀ

	/*������ʼ��*/
	core_params->p_outlayer = new bp_out_layer_params;
	if (core_params->p_outlayer == NULL)
	{
		return -1;
	}
	core_params->p_outlayer->out_num = Out_Num;//�����ڵ���Ŀ   

	/*��������ݻ�������*/
	core_params->p_inlayer->in_buf = alloc_1d_double_buf(core_params->p_inlayer->in_num + 1);//�����Ļ���
	core_params->p_inlayer->weight = alloc_2d_double_buf(core_params->p_inlayer->in_num + 1, core_params->p_hidlayer->hid_num + 1);//����2άȨ�����ݻ���
	core_params->p_inlayer->weight_size = (core_params->p_inlayer->in_num + 1)*(core_params->p_hidlayer->hid_num + 1)*sizeof(double);
	
	core_params->p_inlayer->deltas = alloc_1d_double_buf(core_params->p_hidlayer->hid_num + 1);//����ڵ������Ҫ��deltas��Ŀ
	printf("in buf new ok\n");
	/*���ز����ݻ�������*/
	core_params->p_hidlayer->hid_buf = alloc_1d_double_buf(core_params->p_hidlayer->hid_num + 1);//���ز�Ļ���
	core_params->p_hidlayer->weight = alloc_2d_double_buf(core_params->p_hidlayer->hid_num + 1, core_params->p_outlayer->out_num + 1);//����2άȨ�����ݻ���
	core_params->p_hidlayer->weight_size = (core_params->p_hidlayer->hid_num + 1)*(core_params->p_outlayer->out_num + 1)*sizeof(double);

	core_params->p_hidlayer->deltas = alloc_1d_double_buf(core_params->p_outlayer->out_num + 1);//����ڵ������Ҫ��deltas��Ŀ
	printf("hidden buf new ok\n");
	/*��������ݻ�������*/
	core_params->p_outlayer->out_buf = alloc_1d_double_buf(core_params->p_outlayer->out_num + 1);
	core_params->p_outlayer->out_target = alloc_1d_double_buf(core_params->p_outlayer->out_num + 1);
	printf("out buf new ok\n");
	return 0;
}
//initial bp weight
int init_bp_weight(bp_alg_core_params *core_params)
{

	if (core_params == NULL)
	{
		return -1;
	}

	time_t t;
	bp_random_seed((unsigned)time(&t));

	bp_randomize_weights(core_params->p_inlayer->weight, core_params->p_inlayer->in_num, core_params->p_hidlayer->hid_num);
	bp_randomize_weights(core_params->p_hidlayer->weight, core_params->p_hidlayer->hid_num, core_params->p_outlayer->out_num);


	return 0;

}

//����һ����ƽڵ�ֵ
void bp_layerforward(double *in_node, double *out_node, unsigned int in_num, unsigned int out_num, double **weight)
{
	unsigned int i, j;
	double sum;


	in_node[0] = 1.0; //���ڶ�����ڵ���ֵ����

	for (i = 1; i <= out_num; i++)
	{
		sum = 0.0;

		for (j = 0; j <= in_num; j++)
		{
			sum += weight[j][i] * in_node[j]; //��Ȩ�صĴ���
		}

		
		out_node[i] = squash(sum); //����S�̼������Ľڵ���
	}

}
//����������ز�ĸ��ڵ�������
void bp_outlayer_deltas(double *out_node, double *target, unsigned int node_num, double *hid_deltas)
{
	unsigned int i;
	double o, t;

	for (i = 1; i <= node_num; i++)
	{

		o = out_node[i];//ʵ�����
		t = target[i]; //Ŀ���������
		hid_deltas[i] = (t - o)*o*(1 - o);//��Ӧÿ�������ڵ�Ľ�����
	}

}
 //���ز��������ĸ��ڵ�������

void bp_hidlayer_deltas(double *hid_node, unsigned int hid_num, unsigned int out_num, double **weight, double *hid_deltas, double *in_deltas)
{
	unsigned int i, j;
	double y;
	double sum;

	for (i = 1; i <= hid_num; i++)
	{
		y = hid_node[i]; //���yi
		sum = 0.0;
		for (j = 1; j <= out_num; j++)
		{
			sum += weight[i][j] * hid_deltas[j];//��������ǰһ��Ľ�����Ϣ��Ȩ��ֵ
		}

		in_deltas[i] = sum*y*(1 - y);//��Ӧÿ�����ز�ڵ�Ľ�����
	}

}

//������һ����ڵ�������������һ������֮�������Ȩֵ
void adjust_layer_weight(double *layer1_node, double **weight, double *deltas, unsigned int layer1_num, unsigned int layer2_num, double eta)
{
	unsigned int i, j;
	double node;
	double new_delta;

	layer1_node[0] = 1.0; //��ֵ��ֵ

	for (i = 1; i <= layer2_num; i++)
	{
		for (j = 0; j <= layer1_num; j++)
		{
			new_delta = eta*deltas[i] * layer1_node[j];
			weight[j][i] += new_delta;//Ȩֵ����

		}

	}

}

double calculate_err2(double *target, double *out, unsigned int num)
{
	unsigned int i;
	double err2 = 0.0;
	//printf("\n%%%%\n");
	for (i = 1; i <= num; i++)
	{
		err2 += (target[i] - out[i]) * (target[i] - out[i]);//����
	}
	return err2;

}

int bp_train(bp_alg_core_params *core_params, Sample_Feature_Vec *sam)
{
	unsigned int i, j, k;
	unsigned int train_num, sample_num;
	double err2;//�������

	if (core_params == NULL)
	{
		return -1;
	}

	train_num = core_params->train_ite_num;//����ѵ������
	sample_num = core_params->sample_num;//������

	hd_input_layer_params p_inlayer = core_params->p_inlayer;  //��������
	hd_hidden_layer_params p_hidlayer = core_params->p_hidlayer; //���ز����
	hd_out_layer_params p_outlayer = core_params->p_outlayer; //��������

	/*���ΰ���ѵ��������Ŀ���е���ѵ��*/
	for (i = 0; i < train_num; i++)
	{
		err2 = 0.0;


		for (j = 0; j < sample_num; j++)
		{
			TransformBYTE2Double((sam->pSample + j*p_inlayer->in_num),(p_inlayer->in_buf + 1),(p_inlayer->in_num));
			memcpy((unsigned char*)(p_outlayer->out_target + 1), (unsigned char*)(sam->pTarget + j*p_outlayer->out_num), p_outlayer->out_num*sizeof(double));

			/*����㵽���ز����ǰ�������*/
			bp_layerforward(p_inlayer->in_buf, p_hidlayer->hid_buf, p_inlayer->in_num, p_hidlayer->hid_num, p_inlayer->weight);

			/*���ز㵽��������ǰ�������*/
			bp_layerforward(p_hidlayer->hid_buf, p_outlayer->out_buf, p_hidlayer->hid_num, p_outlayer->out_num, p_hidlayer->weight);

			/*�������ǰ�����������ز㣬��Ȩֵ����ֵ*/
			bp_outlayer_deltas(p_outlayer->out_buf, p_outlayer->out_target, p_outlayer->out_num, p_hidlayer->deltas);

			/*���ز���ǰ������������㣬Ȩֵ����ֵ��������һ��ĵ���ֵ*/
			bp_hidlayer_deltas(p_hidlayer->hid_buf, p_hidlayer->hid_num, p_outlayer->out_num, p_hidlayer->weight, p_hidlayer->deltas, p_inlayer->deltas);

			/*�������ز㵽������Ȩֵ*/
			adjust_layer_weight(p_hidlayer->hid_buf, p_hidlayer->weight, p_hidlayer->deltas, p_hidlayer->hid_num,
				p_outlayer->out_num, core_params->eta);

			/*�������ز㵽������Ȩֵ*/
			adjust_layer_weight(p_inlayer->in_buf, p_inlayer->weight, p_inlayer->deltas, p_inlayer->in_num,
				p_hidlayer->hid_num, core_params->eta);

			err2 += calculate_err2(p_outlayer->out_buf, p_outlayer->out_target, p_outlayer->out_num);//ͳ��������������һ�κ�ľ������
	

		}

		/*һ�����������ľ������ͳ��*/
		err2 = err2 / (double)(p_outlayer->out_num*sample_num);
		printf("err2 =%8lf\n%%%%%\n", err2);

		if (err2 < core_params->err2_thresh)
		{
			printf("BP Train Success by costs vaild iter nums: %d\n", i);
			system("pause");
			return 1;
		}
	}

	printf("BP Train %d Num Failured! need to modfiy core params\n", i);
	return 0;

}


void recognise(bp_alg_core_params *core_params, double *input)
{
	unsigned int i, j;
	unsigned int result = 0;

	if (core_params == NULL)
	{
		//return -1;
	}

	hd_input_layer_params p_inlayer = core_params->p_inlayer;  //��������
	hd_hidden_layer_params p_hidlayer = core_params->p_hidlayer; //���ز����
	hd_out_layer_params p_outlayer = core_params->p_outlayer; //��������

	memcpy((unsigned char*)(p_inlayer->in_buf + 1), (unsigned char*)input, p_inlayer->in_num*sizeof(double));

	/*����㵽���ز����ǰ�������*/                                                                                                                                                                                                                                                                                                                                              
	bp_layerforward(p_inlayer->in_buf, p_hidlayer->hid_buf, p_inlayer->in_num, p_hidlayer->hid_num, p_inlayer->weight);

	/*���ز㵽��������ǰ�������*/
	bp_layerforward(p_hidlayer->hid_buf, p_outlayer->out_buf, p_hidlayer->hid_num, p_outlayer->out_num, p_hidlayer->weight);



	for (int i = 1; i <= p_outlayer->out_num; i++)
	{
		printf("%lf  ", p_outlayer->out_buf[i]);
	}
	printf("\n");
}




