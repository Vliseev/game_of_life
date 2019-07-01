import argparse
from typing import Any, Dict, Tuple

import h5py
import numpy as np
from keras import Input, Model, layers
from sklearn.model_selection import train_test_split


def get_parser():
    parser = argparse.ArgumentParser()
    parser.add_argument("--shape", nargs='+', type=int)
    parser.add_argument('--filters', default=50,
                        help='number layers in first layer')
    parser.add_argument('--path-to-dataset', type=str, required=True)
    parser.add_argument('--model-path', type=str, required=True)
    parser.add_argument('--kernel-size', nargs='+', type=int, default=[3, 3])
    parser.add_argument('--hidden-dim', nargs='+', type=int, default=[100, 50])
    parser.add_argument('--test-size', type=float, default=0.3)
    parser.add_argument('--seed', type=int, default=42)
    parser.add_argument('--num-epoch', type=int, default=40)
    parser.add_argument('--batch-size', type=int, default=1024)
    args = parser.parse_args()
    return args


def reshape_input(X: np.ndarray) -> np.ndarray:
    return X.reshape(X.shape[0], X.shape[1], X.shape[2], 1)


def pad_input(X: np.ndarray, shape: Tuple[int, int]) -> np.ndarray:
    return reshape_input(np.array([
        np.pad(x.reshape(shape), (1, 1), mode='wrap')
        for x in X
    ]))


def build_model(inp_shape: Tuple[int, int],
                filters: int,
                kernel_size=Tuple[int, int],
                hidden_dims=Tuple[int, int]) -> Model:
    inp = Input(shape=(inp_shape[0], inp_shape[1], 1), name='inp')
    x = layers.Conv2D(
        filters,
        kernel_size,
        padding='valid',
        activation='relu',
        strides=1,
        name='conv1'
    )(inp)
    x = layers.Dense(hidden_dims[0], activation='relu', name='dense1')(x)
    x = layers.Conv2D(
        filters,
        kernel_size,
        padding='same',
        activation='relu',
        strides=1,
        name='conv2'
    )(x)
    x = layers.Dense(hidden_dims[1], activation='relu', name='dense2')(x)
    out = layers.Dense(1, activation='sigmoid', name='out')(x)

    return Model([inp], [out])


def read_data(path) -> Tuple[Any, Any]:
    with h5py.File(path) as f:
        X = f["x_train"][:]
        Y = f["y_train"][:]

    return X, Y


def train(params: Dict[str, Any]):
    # input_shape = params['input_shape']
    filters = params['filters']
    kernel_size = params['kernel_size']
    hidden_dims = params['hidden_dim']
    test_size = params['test_size']
    seed = params['seed']
    num_epoch = params['num_epoch']
    batch_size = params['batch_size']
    model_path = params['model_path']

    X, Y = read_data(params['path_to_dataset'])

    input_shape = X.shape[1:]
    if input_shape != param['shape']:
        raise ValueError("input shape isn't equal dataset shape")

    X_pad = pad_input(X, input_shape)
    Y = reshape_input(Y)

    pad_shape = X_pad.shape[1:]
    model = build_model(pad_shape,
                        filters,
                        kernel_size,
                        hidden_dims)

    X_tr, X_val, Y_tr, Y_val = train_test_split(X_pad,
                                                Y,
                                                test_size=test_size,
                                                random_state=seed)

    model.compile(optimizer='adam',
                  loss='binary_crossentropy',
                  metrics=['accuracy'])

    print(model.summary())

    model.fit(X_tr,
              Y_tr,
              epochs=num_epoch,
              batch_size=batch_size,
              validation_data=(X_val, Y_val))

    model.save(model_path)


if __name__ == '__main__':
    args = get_parser()
    param = vars(args)
    train(param)
