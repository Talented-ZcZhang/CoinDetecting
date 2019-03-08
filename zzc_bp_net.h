
#ifndef _ZZC_BP_NET_H
#define _ZZC_BP_NET_H
#include <stdio.h>
#include <stdlib.h>

	typedef struct {

		unsigned int in_num;  //�����ڵ���Ŀ
		double *in_buf; //�����������ݻ���
		double **weight; //Ȩ�أ���ǰ�����һ���ڵ��Ӧ���������
		unsigned int weight_size;
		double *deltas; //��ǰ��������㷴��������Ȩ�ؽ���

	}bp_input_layer_params;

	typedef bp_input_layer_params* hd_input_layer_params;

	typedef struct {

		unsigned int hid_num; //����ڵ���Ŀ
		double *hid_buf; //����������ݻ���
		double **weight; //Ȩ�أ���ǰ����һ���ڵ��Ӧ����������
		unsigned int weight_size;
		double *deltas; //��ǰ������������������Ȩ�ؽ���ֵ

	}bp_hidden_layer_params;

	typedef bp_hidden_layer_params* hd_hidden_layer_params;


	typedef struct {

		unsigned int out_num;//�����ڵ���Ŀ
		double *out_buf; //�����������ݻ���
		double *out_target;

	}bp_out_layer_params;

	typedef bp_out_layer_params* hd_out_layer_params;


	typedef struct{
		unsigned int size; //�ṹ���С
		unsigned int train_ite_num; //ѵ����������
		unsigned int sample_num;  //��ѵ������������
		double eta;                //ѵ������ֵ��ѧϰЧ��
		double err2_thresh;  //��С�������

		hd_input_layer_params p_inlayer; //��������
		hd_hidden_layer_params p_hidlayer;//���ز����
		hd_out_layer_params p_outlayer;//��������
	} bp_alg_core_params;




	 void adjust_layer_weight(double *layer1_node, double **weight, double *deltas, unsigned int layer1_num, unsigned int layer2_num, double eta);

	 double* alloc_1d_double_buf(unsigned int m);

	 double** alloc_2d_double_buf(unsigned int m, unsigned int n);

	 void bp_hidlayer_deltas(double *hid_node, unsigned int hid_num, unsigned int out_num, double **weight, double *hid_deltas, double *in_deltas);

	 void bp_layerforward(double *in_node, double *out_node, unsigned int in_num, unsigned int out_num, double **weight);

    void bp_outlayer_deltas(double *out_node, double *target, unsigned int node_num, double *hid_deltas);

	 void bp_randomize_weights(double **w, int m, int n);

	 void bp_random_seed(int seed);

	class Sample_Feature_Vec;

	int bp_train(bp_alg_core_params *core_params, Sample_Feature_Vec *sam);

	 void bp_zero_weights(double **w, int m, int n);

	 double calculate_err2(double *target, double *out, unsigned int num);

	 void free_alloc_buf(void *p);

	 double get_random();

	 int init_bp_core_params(bp_alg_core_params *core_params);

	 int init_bp_weight(bp_alg_core_params *core_params);

	double squash(double x);

	 void recognise(bp_alg_core_params *core_params, double *input);




#endif