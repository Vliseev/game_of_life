import argparse
from typing import Any, Dict, Tuple

import h5py
import keras
import numpy as np


def reshape_input(X):
    return X.reshape(X.shape[0], X.shape[1], X.shape[2], 1)


def pad_input(X):
    return reshape_input(np.array([
        np.pad(x.reshape((20, 30)), (1, 1), mode='wrap')
        for x in X
    ]))


def get_parser():
    parser = argparse.ArgumentParser()
    parser.add_argument('--path-to-dataset', type=str, required=True)
    parser.add_argument('--model-path', type=str, required=True)
    args = parser.parse_args()
    return args


def read_data(path_to_data: str) -> Tuple[np.array, np.array]:
    with h5py.File(path_to_data) as f:
        X = f["x_train"][:]
        Y = f["y_train"][:]
    return X, Y


def test_model():
    args = get_parser()

    X, Y = read_data(args.path_to_dataset)
    model = keras.models.load_model(args.model_path)
    print(model.summary())

    N = X.shape[0] * X.shape[1] * X.shape[2]

    X = pad_input(X)
    Y = reshape_input(Y)
    pred = model.predict(X)

    accuracy = 1 - float(np.count_nonzero((pred > 0.5).astype(int) - Y)) / N
    print("accuracy={}".format(accuracy))


if __name__ == '__main__':
    test_model()
