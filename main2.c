#include <stdio.h>

struct sparse {
    int row, col, val;
};

void readinput(int mat[10][10], int *rows, int *cols) {
    printf("Enter the rows and columns respectively\n");
    scanf("%d%d", rows, cols);
    printf("Enter the Elements of matrix\n");
    for (int i = 0; i < *rows; i++) {
        for (int j = 0; j < *cols; j++) {
            scanf("%d", &mat[i][j]);
        }
    }
}

int totriplet(struct sparse triplet[], int rows, int cols, int mat[10][10]) {
    int k = 1;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (mat[i][j] != 0) {
                triplet[k].row = i;
                triplet[k].col = j;
                triplet[k].val = mat[i][j];
                k++;
            }
        }
    }
    triplet[0].row = rows;
    triplet[0].col = cols;
    triplet[0].val = k - 1;
    return k;
}

void Transpose(struct sparse data[], struct sparse transpose[], int n) {
    for (int i = 0; i < n; i++) {
        transpose[i].col = data[i].row;
        transpose[i].row = data[i].col;
        transpose[i].val = data[i].val;
    }
}

void Sum(struct sparse data[], struct sparse transpose[], struct sparse sum[], int n) {
    int i = 1, j = 1, k = 1;
    while (i < n && j < n) {
        if (data[i].row == transpose[j].row && data[i].col == transpose[j].col) {
            sum[k] = data[i];
            sum[k].val += transpose[j].val;
            k++; i++; j++;
        } else if ((data[i].row < transpose[j].row) ||
                   (data[i].row == transpose[j].row && data[i].col < transpose[j].col)) {
            sum[k++] = data[i++];
        } else {
            sum[k++] = transpose[j++];
        }
    }
    while (i < n) sum[k++] = data[i++];
    while (j < n) sum[k++] = transpose[j++];
    
    sum[0].row = data[0].row;
    sum[0].col = data[0].col;
    sum[0].val = k - 1;
}

void sort(struct sparse arr[], int n) {
    for (int i = 1; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (arr[i].row > arr[j].row ||
               (arr[i].row == arr[j].row && arr[i].col > arr[j].col)) {
                struct sparse temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
}

void display(struct sparse triplet[], int n) {
    printf("Row Col Val\n");
    for (int i = 0; i < n; i++)
        printf("%3d %3d %3d\n", triplet[i].row, triplet[i].col, triplet[i].val);
}

int main() {
    int mat[10][10], rows, cols;
    struct sparse data[100], transpose[100], sum[100];
    
    readinput(mat, &rows, &cols);
    
    int n = totriplet(data, rows, cols, mat);
    
    printf("\nOriginal Triplet Format:\n");
    display(data, n);
    
    Transpose(data, transpose, n);
    printf("\nTranspose Triplet Format:\n");
    display(transpose, n);
    
    sort(transpose, n);
    Sum(data, transpose, sum, n);
    
    printf("\nSum Triplet Format:\n");
    display(sum, n);
    
    return 0;
}
