# Practical-1 (K-Nearest Neighbors)

Problem Statement: Implement K-Nearest Neighbors algorithm on `diabetes.csv` dataset. Compute confusion matrix, accuracy, error rate, precision and recall on the given dataset.

> [!NOTE]
> Dataset available in [Datasets](../Datasets/diabetes.csv) directory.

---

## Steps

1. Import libraries
2. Load dataset
3. Handle missing (zero) values
4. Split features and target
5. Train-test split
6. Standardize data
7. Train KNN model
8. Confusion matrix
9. Accuracy, error rate, precision and recall
10. Find best value of k

---

## Code

### 1. Import libraries:

```python3
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import StandardScaler
from sklearn.neighbors import KNeighborsClassifier
from sklearn.metrics import confusion_matrix, accuracy_score, precision_score, recall_score, classification_report
```

### 2. Load dataset:

```python3
df = pd.read_csv("diabetes.csv")
print("Dataset shape:", df.shape)
print(df.head())
print(df.info())
print("\nOutcome counts:\n", df['Outcome'].value_counts())
```

### 3. Handle missing (zero) values:

```python3
# In this dataset, 0 in these columns means the value is missing
cols = ['Glucose', 'BloodPressure', 'SkinThickness', 'Insulin', 'BMI']
df[cols] = df[cols].replace(0, np.nan)

# Replace missing values with the column mean
df[cols] = df[cols].fillna(df[cols].mean())

print("Missing values:\n", df.isnull().sum())
```

### 4. Split features and target:

```python3
X = df.drop('Outcome', axis=1)
y = df['Outcome']
```

### 5. Train-test split:

```python3
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)
print("Train shape:", X_train.shape)
print("Test shape:", X_test.shape)
```

### 6. Standardize data:

```python3
# KNN uses distance, so all features must be on the same scale
scaler = StandardScaler()
X_train = scaler.fit_transform(X_train)
X_test = scaler.transform(X_test)
```

### 7. Train KNN model:

```python3
knn = KNeighborsClassifier(n_neighbors=5)
knn.fit(X_train, y_train)
y_pred = knn.predict(X_test)
```

### 8. Confusion matrix:

```python3
cm = confusion_matrix(y_test, y_pred)
print("Confusion Matrix:\n", cm)

# Visualize confusion matrix
plt.figure(figsize=(5,4))
sns.heatmap(cm, annot=True, fmt='d', cmap='Blues',
            xticklabels=['No Diabetes', 'Diabetes'],
            yticklabels=['No Diabetes', 'Diabetes'])
plt.title('Confusion Matrix')
plt.xlabel('Predicted')
plt.ylabel('Actual')
plt.show()
```

### 9. Accuracy, error rate, precision and recall:

```python3
TN, FP, FN, TP = cm.ravel()
print("TP:", TP, " TN:", TN, " FP:", FP, " FN:", FN)

# Using formulas
accuracy = (TP + TN) / (TP + TN + FP + FN)
error_rate = (FP + FN) / (TP + TN + FP + FN)
precision = TP / (TP + FP)
recall = TP / (TP + FN)

print("\nAccuracy   :", round(accuracy, 4))
print("Error Rate :", round(error_rate, 4))
print("Precision  :", round(precision, 4))
print("Recall     :", round(recall, 4))

# Using sklearn (to verify)
print("\nsklearn Accuracy  :", round(accuracy_score(y_test, y_pred), 4))
print("sklearn Error Rate:", round(1 - accuracy_score(y_test, y_pred), 4))
print("sklearn Precision :", round(precision_score(y_test, y_pred), 4))
print("sklearn Recall    :", round(recall_score(y_test, y_pred), 4))

print("\nClassification Report:\n", classification_report(y_test, y_pred))
```

### 10. Find best value of k:

```python3
error_rates = []
for k in range(1, 21):
    model = KNeighborsClassifier(n_neighbors=k)
    model.fit(X_train, y_train)
    pred_k = model.predict(X_test)
    error_rates.append(np.mean(pred_k != y_test))

# Plot error rate vs k
plt.figure(figsize=(6,4))
plt.plot(range(1, 21), error_rates, marker='o')
plt.title('Error Rate vs K Value')
plt.xlabel('K')
plt.ylabel('Error Rate')
plt.show()

best_k = error_rates.index(min(error_rates)) + 1
print("Best k:", best_k, " Error rate:", round(min(error_rates), 4))
```

---

## Miscellaneous

- [Dataset source](https://www.kaggle.com/datasets/abdallamahgoub/diabetes)

---
