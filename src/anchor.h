#ifndef ANCHOR_H
#define ANCHOR_H
#include <stdint.h>
#include <stdbool.h>

#define ANCHOR_W 16
#define ANCHOR_H 16
#define GRID_CNT 4
#define SUB_W 8
#define SUB_H 8

typedef struct {
    double x, y;
    int id;
} AnchorPoint;

bool anchor_embed(uint8_t *rgb, int w, int h, AnchorPoint *out_grid);
int anchor_detect(uint8_t *rgb, int w, int h, AnchorPoint *detected, int max_det);
bool affine_estimate(AnchorPoint *src, AnchorPoint *dst, int n, double *affine);
bool inv_similar(double *A, double *invA);
bool affine_warp(uint8_t *in_rgb, int w, int h, double *affine, uint8_t *out_rgb);

#endif