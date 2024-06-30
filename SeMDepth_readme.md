# SeMDepth 结合语义信息的深度估计模型

## Train

### 训练SeMDepth语义编码器
使用`./Eecoder_train.py`来训练语义信息编码器，你需要准备Cityscapes数据集来完成这一步骤
```python
python ./Eecoder_train.py --root_dir "Your Sementic Datasets Directory"
```
### 训练新的SeMDepth
使用`./Train_SeMDepth.py`来训练一个SeMDepth模型，你需要准备kitti数据集来完成这一步骤，使用Eigen_zhou分割，数据集的准备详见[MonoDepth2](https://github.com/nianticlabs/monodepth2)
```python
python ./Train_SeMDepth.py --data_path "Your Kitti Datasets Directory" --model_name mytrain --num_epochs 30 --batch_size 12 --lr 0.0001 5e-6 31 0.0001 1e-5 31
```

## Test
你需要训练好的模型encoder与decoder来查看分割网络的训练结果
使用以下代码测试SeMDepth以获取可视化结果，请注意，你需要更改path为图片地址，encoder与decoder可使用`./tmp/Segment_119/`下的预训练模型
```python
python ./Test_eg.py
```

你需要使用训练好的encoder与decoder来查看SeMDepth的训练结果
你可以直接使用lite-mono的test脚本，SeMDepth只是在训练时使其关注语义信息
```python
python ./Test_simple.py --image_path "Your Test DataSets" --load_weights_folder "Your Pretrained weights" --ext "Data suffix, None if .jpg"
```
我们提供了两种预训练模型
1. 使用kitti数据集对SeMDepth的训练结果，位于`./Pretrained/Seg-Mono_116_noPreatrained`
2. 相同条件下对light-mono进行训练的训练结果，位于`./Pretrained/Lite-Mono_noPretrained`

## Eval
目前只提供对Kitti数据集的量化结果评估，你需要按照[MonoDepth2](https://github.com/nianticlabs/monodepth2)中的提示准备kitti数据集的真值，`export_gt_depth.py`文件并不包含在此目录下，请从MonoDepth2中获取。
```python
python export_gt_depth.py --data_path kitti_data --split eigen
python export_gt_depth.py --data_path kitti_data --split eigen_benchmark
```
获取真值后，你可以使用以下命令进行量化结果评估
```python
python ./Evaluate_depth.py --data_path "Kitti DataSets" --load_weights_folder "Your Pretrained weights"
```
***
无投稿后续需求




