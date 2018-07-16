#include <iostream>
#include <fstream>
#include <string>
#include <vector>

/*
    Verilen const char pointer'in verilen delimiter'a gore parcalayip
    std::vector yapan fonksiyon
*/
std::vector<std::string> split(const char *str, char c = ' ')
{
    std::vector<std::string> result;

    do
    {
        const char *begin = str;

        while (*str != c && *str)
            str++;

        result.push_back(std::string(begin, str));
    } while (0 != *str++);

    return result;
}
#include <svm.h>

svm_problem*
parse_train_data(std::string filename)
{
    svm_problem *ret = new svm_problem;
    // Uc alan var l, y, ve x
    // l: Length
    // y: Label: etiketler
    // x: X: egitim verisi
    // Dosyayi acip alanlari oku
    std::ifstream inf(filename);
    std::string line;
    std::getline(inf, line); // ilk satiri yoksay
    std::vector<svm_node*> table;
    std::vector<double> labels;
    int counter = 0;
    while (std::getline(inf, line))
    {
        counter += 1;
        std::vector<std::string> tokens = split(line.c_str(), ',');
        svm_node* data = new svm_node[tokens.size()];
        for (int i = 0; i < tokens.size() - 1; i++)
        {
            data[i].index = i;
            data[i].value = std::stoi(tokens[i]);
        }
        data[tokens.size()].index = -1;
        table.push_back(data);
        labels.push_back(std::stoi(tokens[tokens.size() -1 ]));
    }
    ret->l = counter;
    std::cout << ret->l << std::endl;
    ret->y = new double[ret->l];
    ret->x = new svm_node*[ret->l];
    for(int i = 0;i < ret->l;i++)
    {
        ret->y[i] = labels[i];
        ret->x[i] = table[i];
    }
    inf.close();
    return ret;
}

int main(int argc, char **argv)
{
    std::string filename = argv[1];
    svm_problem* problem = parse_train_data(filename);
    svm_parameter param;
    
    param.svm_type = C_SVC;
	param.kernel_type = RBF;
	param.degree = 3;
	param.gamma = 0;	// 1/num_features
	param.coef0 = 0;
	param.nu = 0.5;
	param.cache_size = 100;
	param.C = 1;
	param.eps = 1e-3;
	param.p = 0.1;
	param.shrinking = 1;
	param.probability = 0;
	param.nr_weight = 0;
	param.weight_label = NULL;
	param.weight = NULL;

    // parametrelerin icini doldur
    svm_model *model = svm_train(problem, &param);
    // 6.7 3.3 5.7 2.5
    double data[4] = {6.5, 3.2, 5.1, 2.0};
    svm_node *query_data = new svm_node[4];
    for (int i = 0; i < 4; i++)
    {
        query_data[i].index = i;
        query_data[i].value = data[i];
    }

    std::cout << "Sonuc:" << svm_predict(model, query_data) << std::endl;
    svm_save_model("model", model);

    svm_free_and_destroy_model(&model);
    delete problem->y;
    for(int i = 0;i < problem->l;i++)
    {   
        delete problem->x[i];
    }
    delete problem->x;
    delete problem;
    return 0;
}
