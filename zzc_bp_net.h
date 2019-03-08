
#ifndef _ZZC_BP_NET_H
#define _ZZC_BP_NET_H
#include <stdio.h>
#include <stdlib.h>

	typedef struct {

		unsigned int in_num;  //输入层节点数目
		double *in_buf; //输入层输出数据缓存
		double **weight; //权重，当前输入层一个节点对应到多个隐层
		unsigned int weight_size;
		double *deltas; //当前计算的隐层反馈回来的权重矫正

	}bp_input_layer_params;

	typedef bp_input_layer_params* hd_input_layer_params;

	typedef struct {

		unsigned int hid_num; //隐层节点数目
		double *hid_buf; //隐层输出数据缓存
		double **weight; //权重，当前隐层一个节点对应到多个输出层
		unsigned int weight_size;
		double *deltas; //当前计算的输出反馈回来的权重矫正值

	}bp_hidden_layer_params;

	typedef bp_hidden_layer_params* hd_hidden_layer_params;


	typedef struct {

		unsigned int out_num;//输出层节点数目
		double *out_buf; //输出层输出数据缓存
		double *out_target;

	}bp_out_layer_params;

	typedef bp_out_layer_params* hd_out_layer_params;


	typedef struct{
		unsigned int size; //结构体大小
		unsigned int train_ite_num; //训练迭代次数
		unsigned int sample_num;  //待训练的样本个数
		double eta;                //训练步进值，学习效率
		double err2_thresh;  //最小均方误差

		hd_input_layer_params p_inlayer; //输入层参数
		hd_hidden_layer_params p_hidlayer;//隐藏层参数
		hd_out_layer_params p_outlayer;//输出层参数
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