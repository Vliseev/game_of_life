# 1. cpp_backend.
 Реализация на c++, версия компилятора gcc-7.4. В папке tests находятся юнит-тесты `google-tests`

# 2. pyhton.
`gof_nn.py` скрипт для обучения нейросети, параметры:

```
--shape SHAPE [SHAPE ...] размер поля
--filters FILTERS  количество фильтров на первом слое
--path-to-dataset PATH_TO_DATASET путь к датасету
--model-path MODEL_PATH путь путь для сохранения модели
--kernel-size KERNEL_SIZE [KERNEL_SIZE ...] размер свертки, по умолчанию 3 3
--hidden-dim HIDDEN_DIM [HIDDEN_DIM ...] размерность двух полносвязных слоев, по умолчанию 100 50 
--test-size TEST_SIZE доля валидационной выборки, по умолчанию 0.3
--seed SEED
--num-epoch NUM_EPOCH
--batch-size BATCH_SIZE

```
`test_model.py` скрипт для тестирования модели.
```
  --path-to-dataset PATH_TO_DATASET
  --model-path MODEL_PATH
```

В репозитарии лежит модель (`gol.h5`), обученная на поле размера 20x30. 