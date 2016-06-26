#include "Silhouettes_counter.h"

Silhouettes_counter :: Silhouettes_counter() {
}

/* @param point 0 - GPoint
 * @param width - width of the array
 * @param height  - the height of the array
 * Return true if point is lying within the two-dimensional array */
bool isArrayRange(QPoint point, int height, int width) {
    int x = point.x();
    int y = point.y();
    if (x >= 0 && x < width && y >= 0 && y < height)
        return true;
    return false;
}

/* @param point - current point of the image, it is or a silhouelette or a canvas
 * @param width - width of the array
 * @param height  - the height of the array
 * @param imageLight - matrix of lightness
 * Does bypass of the silhoulette*/
void Silhouettes_counter :: fillSilhoulette(QPoint &point, int** imageLight, int height, int width, int canvasColor) {
    queue<QPoint>* q = new queue<QPoint>;
    imageLight[point.y()][point.x()] = canvasColor;
    q->push(point);
    while(q->size()) {
        QPoint tmp = q->front();
        q->pop();
        int x = tmp.x();
        int y = tmp.y();
        for (int i = -1; i < 2; i++) {
            for (int j = -1; j < 2; j++) {
                if (isArrayRange(QPoint(x + j, y + i), height, width) && imageLight[y + i][x + j] != canvasColor) {
                    imageLight[y + i][x + j]  = canvasColor;
                    q->push(QPoint(x + j, y + i));
                }
            }
        }
    }
}

/* Return a count of the silhoulettes standing separately*/
int Silhouettes_counter :: count(string filePath) {
    QImage* image = new QImage(filePath.c_str());
    int height = image->height();
    int width = image->width();
    int** imageLight = new int*[height];
    for (int i = 0; i < height; i++) {
        imageLight[i] = new int[width];
    }
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            QColor tempColor = image->pixel(j, i);
            imageLight[i][j] = tempColor.lightness();
        }
    }
    map<int, int>* colorMap = new  map<int, int>;
    for(int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            (*colorMap)[imageLight[i][j] ] ++;
        }
    }
    map<int, int> :: iterator iter;

    int color1[2] = {0, 0};
    for (iter = colorMap->begin(); iter != colorMap->end(); iter++) {
        if (iter->second > color1[1]) {
            color1[1] = iter->second;
            color1[0] = iter->first;
        }
    }
    int color2[2] = {0, 0};
    for (iter = colorMap->begin(); iter != colorMap->end(); iter++) {
        if (iter->second > color2[1] && iter->first != color1[0]) {
            color2[1] = iter->second;
            color2[0] = iter->first;
        }
    }

    int colorMedian = (color1[0] + color2[0]) / 2;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (imageLight[i][j] < colorMedian)
                imageLight[i][j] = 0;
            else
                imageLight[i][j] = 1;
        }
    }


    int zeroCounter = 0;
    int oneCounter = 0;
    for (int i = 0; i < width; i++) {
        if (imageLight[0][i] > 0) {
            oneCounter++;
        }
        else {
            zeroCounter++;
        }
        if (imageLight[height - 1][i] > 0) {
            oneCounter++;
        }
        else {
            zeroCounter++;
        }
    }

    for (int i = 0; i < height; i++) {
        if (imageLight[i][width - 1] > 0) {
            oneCounter++;
        }
        else {
            zeroCounter++;
        }
        if (imageLight[i][0] > 0) {
            oneCounter++;
        }
        else {
            zeroCounter++;
        }

    }

    int canvasColor = 0;
    if (oneCounter >= zeroCounter) {
        canvasColor = 1;
    }

    int result = 0;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (imageLight[i][j] != canvasColor) {
                QPoint point;
                point.setX(j);
                point.setY(i);
                fillSilhoulette(point, imageLight, height, width, canvasColor);
                result++;
            }
        }
    }
    return result;
}

