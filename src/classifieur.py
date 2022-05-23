import pandas as pd
import matplotlib.pyplot as plt
from sklearn.preprocessing import LabelEncoder, RobustScaler
from sklearn.model_selection import train_test_split
from sklearn.datasets import make_classification
from sklearn.metrics import confusion_matrix
from sklearn.svm import LinearSVC
import numpy as np

#from sklearn.metrics import plot_confusion_matrix
#from sklearn.metrics import ConfusionMatrixDisplay

### Entraînement du classifieur

PATH = r'matrix.csv'

dataset = np.genfromtxt(PATH, delimiter=";")

features = dataset[:, 1:-1] # prend tout le tableau sauf la première et la dernière colonne.

print(f"Le tableau des descripteurs est de dimension : {features.shape}.")



def normalize(X):
    '''
    Batch normalization
    '''
    X_normalized = np.zeros((X.shape))
    for j in range(X.shape[1]):
        mean = np.mean(X[:, j])
        std = np.std(X[:, j])
        for i in range(X.shape[0]):
            X_normalized[i, j] = (X[i, j] - mean) / (std + 0.000001)
    return X_normalized

#features=normalize(features)

# Il devrait être de dimensions 1000 x 514, si le nombre de colonne n'est pas le bon vous pouvez modifier features = dataset[:, 1:-1] par features = dataset[:, 1:-2] (cela supprime les 2 dernières colonnes)

y = dataset[:, 0]

X_train, X_test, y_train, y_test = train_test_split(features, y, test_size=0.2, random_state=0)

# model = LinearSVC(C=0.1, max_iter=100, tol=1e-4) #0.2 // bash 0.29
model = LinearSVC(C=0.1, max_iter=100, tol=1e-4) # 0.3

# On peut modifier les paramètres C, max_iter et tol, pour augmenter la performance du modèle.

model.fit(X_train, y_train)

print("Performances du modèle sur la base de données de test : ", model.score(X_test, y_test))


### Save W and b

# b = model.intercept_
# w = model.coef_

# np.savetxt("path to w", w, fmt='%.4f',delimiter=",")
# np.savetxt("path to b", b, fmt='%.4f',delimiter=",")


## Plot Confusion Matrix
def plot_confusion_matrix(y_true, y_pred, classes,
                          normalize=False,
                          title=None,
                          cmap=plt.cm.Blues):
    """
    This function prints and plots the confusion matrix.
    Normalization can be applied by setting `normalize=True`.
    """
    if not title:
        if normalize:
            title = 'Normalized confusion matrix'
        else:
            title = 'Confusion matrix, without normalization'

    # Compute confusion matrix
    cm = confusion_matrix(y_true, y_pred)
    # Only use the labels that appear in the data
    # classes = classes[unique_labels(y_true, y_pred)]
    if normalize:
        cm = cm.astype('float') / cm.sum(axis=1)[:, np.newaxis]
        print("Normalized confusion matrix")
    else:
        print('Confusion matrix, without normalization')

    print(cm)

    fig, ax = plt.subplots()
    im = ax.imshow(cm, interpolation='nearest', cmap=cmap)
    ax.figure.colorbar(im, ax=ax)
    # We want to show all ticks...
    ax.set(xticks=np.arange(cm.shape[1]),
           yticks=np.arange(cm.shape[0]),
           # ... and label them with the respective list entries
           xticklabels=classes, yticklabels=classes,
           title=title,
           ylabel='True label',
           xlabel='Predicted label')

    # Rotate the tick labels and set their alignment.
    plt.setp(ax.get_xticklabels(), rotation=45, ha="right",
             rotation_mode="anchor")

    # Loop over data dimensions and create text annotations.
    fmt = '.2f' if normalize else 'd'
    thresh = cm.max() / 2.
    for i in range(cm.shape[0]):
        for j in range(cm.shape[1]):
            ax.text(j, i, format(cm[i, j], fmt),
                    ha="center", va="center",
                    color="white" if cm[i, j] > thresh else "black")
    fig.tight_layout()
    plt.xlim(-0.5, len(np.unique(y))-0.5)
    plt.ylim(len(np.unique(y))-0.5, -0.5)
    return ax



y_true = np.zeros((200),dtype=float)
for i in range(200):
    y_true[i]=i//20

labels = ['blues', 'classical', 'country', 'disco', 'hiphop', 'jazz', 'metal', 'pop', 'reggae', 'rock']

np.set_printoptions(precision=1)

# Plot non-normalized confusion matrix
plot_confusion_matrix(y_test, y_true, classes=labels, normalize='true')

plt.show()


### Technique pour obtenir une nette amélioration des performances : normaliser les entrées du classifieur avec la batch normalization (Xi - mean / (std + epsilon))
