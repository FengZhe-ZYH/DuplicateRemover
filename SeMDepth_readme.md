# SeMDepth 结合语义信息的深度估计模型

## Train

### 训练SeMDepth语义编码器
使用`./Eecoder_train.py`来训练语义信息编码器，你需要准备Cityscapes数据集来完成这一步骤
```python
python ./Eecoder_train.py --root_dir "Your Sementic Datasets Directory"
```
### 训练新的SeMDepth
使用`./Train_SeMDepth.py`来训练一个SeMDepth模型，你需要准备kitti数据集来完成这一步骤
```python
python ./Train_SeMDepth.py --data_path "Your Kitti Datasets Directory"
```

## Test
你需要训练好的模型encoder与decoder来查看分割网络的训练结果
使用以下代码测试SeMDepth以获取可视化结果，请注意，你需要更改path为图片地址，encoder与decoder可使用`./tmp/Segment_119/`下的预训练模型
```python
python ./test_eg.py
```

你需要使用训练好的encoder与decoder来查看SeMDepth的训练结果
你可以直接使用lite-mono的test脚本，SeMDepth只是在训练时使其关注语义信息
```python
python .\test_simple.py --image_path "Your Test DataSets" --load_weights_folder "Your Pretrained weights"
```
我们提供了两种预训练模型
1. 使用kitti数据集对SeMDepth的训练结果，位于`./Pretrained/Seg-Mono_116_noPreatrained`
2. 相同条件下对ligh



