# Practical-6 (Clustering)

Problem Statement: Implement K-Means clustering/ hierarchical clustering on `sales_data_sample.csv` dataset. Determine the number of clusters using the elbow method.

> [!NOTE]
> Dataset available in [Datasets](../Datasets/sales_data_sample.csv) directory.

---
 
## Steps

1. Import libraries
2. Load dataset
3. Select numerical features for clustering
4. Standarize data
5. K-Means clustering
6. Hierarchical clustering

---

## Code

### 1. Import libraries:

```python3
import pandas as pd
import matplotlib.pyplot as plt
from sklearn.preprocessing import StandardScaler
from sklearn.cluster import KMeans
from scipy.cluster.hierarchy import linkage, dendrogram, fcluster
import seaborn as sns
```

### 2. Load dataset:

```python3
df = pd.read_csv("sales_data_sample.csv", encoding='latin1', on_bad_lines='skip')
print("Dataset shape:", df.shape)
print(df.head())
```

### 3. Select numerical features for clustering:

```python3
X = df.select_dtypes(include=['int64', 'float64'])
print("Features used for clustering:\n", X.head())

# Select relevant numeric columns
# X = df[['SALES', 'QUANTITYORDERED', 'PRICEEACH']]

# Handle missing values if any
# X = features.dropna()
```

### 4. Standardize data:

```python3
scaler = StandardScaler()
X_scaled = scaler.fit_transform(X)
```

### 5. K-Means clustering:

```python3
# Determine optimal number of clusters using Elbow Method
wcss = []
for k in range(1, 11):
    kmeans = KMeans(n_clusters=k, random_state=42)
    kmeans.fit(X_scaled)
    wcss.append(kmeans.inertia_)

# Plot Elbow Method
plt.figure(figsize=(6,4))
plt.plot(range(1, 11), wcss, marker='o')
plt.title('Elbow Method')
plt.xlabel('Number of clusters (k)')
plt.ylabel('Inertia (WCSS)')
plt.show()

# Fit KMeans with chosen number of clusters (example: 3 clusters)
kmeans = KMeans(n_clusters=3, random_state=42) # Add n_init=10 param in the function to suppress warnings
clusters_kmeans = kmeans.fit_predict(X_scaled)
df['KMeans_Cluster'] = clusters_kmeans

# Visualize clusters
sns.scatterplot(x='SALES', y='PRICEEACH', hue='KMeans_Cluster', data=df, palette='viridis')
plt.title("K-Means Clustering")
plt.show()

print("\nK-Means Cluster Centers:\n", kmeans.cluster_centers_)
print("\nCluster counts:\n", df['KMeans_Cluster'].value_counts())
```

### 6. Hierarchical clustering:

```python3
# Create linkage matrix
Z = linkage(X_scaled, method='ward')

# Plot dendrogram
plt.figure(figsize=(10,5))
dendrogram(Z)
plt.title('Hierarchical Clustering Dendrogram')
plt.xlabel('Samples')
plt.ylabel('Distance')
plt.show()

# Assign clusters (example: 3 clusters)
clusters_hier = fcluster(Z, t=3, criterion='maxclust')
df['Hierarchical_Cluster'] = clusters_hier

print("\nHierarchical Cluster counts:\n", pd.Series(clusters_hier).value_counts())
```

---

## Miscellaneous

- [Dataset source](https://www.kaggle.com/datasets/kyanyoga/sample-sales-data)

---
