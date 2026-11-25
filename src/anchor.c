#include "anchor.h"
#include <string.h>
#include <math.h>

static const uint8_t anchor_code[4] = {1,0,1,0};

static void draw_lowfreq_anchor(uint8_t *img, int cx, int cy, int w, int h)
{
    for(int bid=0;bid<4;bid++){
        int off_x = (bid%2)*SUB_W;
        int off_y = (bid/2)*SUB_H;
        uint8_t color = anchor_code[bid] ? 255 : 0;
        for(int dy=0;dy<SUB_H;dy++){
            for(int dx=0;dx<SUB_W;dx++){
                int px = cx - ANCHOR_W/2 + off_x + dx;
                int py = cy - ANCHOR_H/2 + off_y + dy;
                if(px >=0 && px < w && py >=0 && py < h){
                    int pos = (py * w + px)*3;
                    img[pos] = color;
                    img[pos+1] = color;
                    img[pos+2] = color;
                }
            }
        }
    }
}

bool anchor_embed(uint8_t *rgb, int w, int h, AnchorPoint *out_grid) {
    int step_x = w / (GRID_CNT + 1);
    int step_y = h / (GRID_CNT + 1);
    int idx = 0;
    for(int gy=1; gy<=GRID_CNT; gy++){
        for(int gx=1; gx<=GRID_CNT; gx++){
            int cx = gx * step_x;
            int cy = gy * step_y;
            out_grid[idx++] = (AnchorPoint){cx, cy, idx-1};
            draw_lowfreq_anchor(rgb, cx, cy, w, h);
        }
    }
    return true;
}

static double ncc_match(uint8_t *img, int w, int h, int sx, int sy){
    double sum_i=0, sum_p=0, sum_ip=0;
    for(int y=0;y<ANCHOR_H;y++){
        for(int x=0;x<ANCHOR_W;x++){
            int px = sx+x;
            int py = sy+y;
            if(px<0||px>=w||py<0||py>=h) return -1;
            int pos = (py*w+px)*3;
            uint8_t iv = img[pos];
            uint8_t pv = ((y<SUB_H&&x<SUB_W) ? anchor_code[0] :
                         (y<SUB_H&&x>=SUB_W) ? anchor_code[1] :
                         (y>=SUB_H&&x<SUB_W) ? anchor_code[2] : anchor_code[3]) ? 255 : 0;
            sum_i += iv; sum_p += pv; sum_ip += iv*pv;
        }
    }
    double mean_i = sum_i/(ANCHOR_W*ANCHOR_H);
    double mean_p = sum_p/(ANCHOR_W*ANCHOR_H);
    double cov = 0, var_i=0, var_p=0;
    for(int y=0;y<ANCHOR_H;y++){
        for(int x=0;x<ANCHOR_W;x++){
            int px = sx+x;
            int py = sy+y;
            int pos = (py*w+px)*3;
            uint8_t iv = img[pos];
            uint8_t pv = ((y<SUB_H&&x<SUB_W) ? anchor_code[0] :
                         (y<SUB_H&&x>=SUB_W) ? anchor_code[1] :
                         (y>=SUB_H&&x<SUB_W) ? anchor_code[2] : anchor_code[3]) ? 255 : 0;
            double di = iv - mean_i;
            double dp = pv - mean_p;
            cov += di*dp;
            var_i += di*di;
            var_p += dp*dp;
        }
    }
    if(var_i < 1e-6 || var_p <1e-6) return -1;
    return cov / sqrt(var_i * var_p);
}

static bool anchor_bit_check(uint8_t *patch)
{
    int err = 0;
    for(int bid=0;bid<4;bid++){
        int off_x = (bid%2)*SUB_W;
        int off_y = (bid/2)*SUB_H;
        int sum = 0;
        for(int dy=0;dy<SUB_H;dy++)
            for(int dx=0;dx<SUB_W;dx++)
                sum += patch[(off_y+dy)*ANCHOR_W + off_x + dx];
        uint8_t bit = (sum/(SUB_W*SUB_H)) > 127 ? 1 : 0;
        if(bit != anchor_code[bid]) err++;
    }
    return err <= 1;
}

int anchor_detect(uint8_t *rgb, int w, int h, AnchorPoint *detected, int max_det) {
    int cnt = 0;
    for(int y=0;y < h - ANCHOR_H; y +=4){
        for(int x=0;x < w - ANCHOR_W; x +=4){
            double score = ncc_match(rgb, w, h, x, y);
            if(score > 0.6 && cnt < max_det){
                uint8_t patch[ANCHOR_H*ANCHOR_W];
                for(int py=0;py<ANCHOR_H;py++)
                    for(int px=0;px<ANCHOR_W;px++)
                        patch[py*ANCHOR_W+px] = rgb[((y+py)*w + x+px)*3];
                if(anchor_bit_check(patch)){
                    detected[cnt++] = (AnchorPoint){x + ANCHOR_W/2.0, y + ANCHOR_H/2.0, -1};
                }
            }
        }
    }
    return cnt;
}

bool affine_estimate(AnchorPoint *src, AnchorPoint *dst, int n, double *affine)
{
    if(n < 3) return false;
    double sum_x=0, sum_y=0, sum_u=0, sum_v=0;
    double sum_xx=0, sum_yy=0, sum_xy=0;
    double sum_xu=0, sum_yu=0, sum_xv=0, sum_yv=0;
    for(int i=0;i<n;i++){
        double x = src[i].x;
        double y = src[i].y;
        double u = dst[i].x;
        double v = dst[i].y;
        sum_x += x; sum_y += y; sum_u += u; sum_v += v;
        sum_xx += x*x; sum_yy += y*y; sum_xy += x*y;
        sum_xu += x*u; sum_yu += y*u;
        sum_xv += x*v; sum_yv += y*v;
    }
    double N = n;
    double mx = sum_x/N, my = sum_y/N;
    double mu = sum_u/N, mv = sum_v/N;
    double A11 = sum_xx - N*mx*mx;
    double A12 = sum_xy - N*mx*my;
    double A21 = A12;
    double A22 = sum_yy - N*my*my;
    double B11 = sum_xu - N*mx*mu;
    double B12 = sum_yu - N*my*mu;
    double B21 = sum_xv - N*mx*mv;
    double B22 = sum_yv - N*my*mv;

    double S1 = A11*B11 + A12*B12;
    double S2 = A11*B21 + A12*B22;
    double S3 = A21*B11 + A22*B12;
    double S4 = A21*B21 + A22*B22;
    double denom = A11*A11 + A12*A12;
    if(fabs(denom) < 1e-9) return false;
    double s_cos = (S1 + S4)/denom/2.0;
    double s_sin = (S3 - S2)/denom/2.0;
    double s = sqrt(s_cos*s_cos + s_sin*s_sin);
    if(s < 0.1 || s > 3.0) return false;
    double c = mu - s_cos*mx + s_sin*my;
    double f = mv - s_sin*mx - s_cos*my;
    affine[0] = s_cos;
    affine[1] = -s_sin;
    affine[2] = c;
    affine[3] = s_sin;
    affine[4] = s_cos;
    affine[5] = f;
    return true;
}

bool inv_similar(double *A, double *invA)
{
    double a = A[0], b = A[1], d = A[3], e = A[4];
    double s2 = a*a + b*b;
    if(s2 < 1e-9) return false;
    invA[0] = a / s2; invA[1] = b / s2;
    invA[3] = -d / s2; invA[4] = a / s2;
    double c = A[2], f = A[5];
    invA[2] = -invA[0]*c - invA[1]*f;
    invA[5] = -invA[3]*c - invA[4]*f;
    return true;
}

bool affine_warp(uint8_t *in_rgb, int w, int h, double *affine, uint8_t *out_rgb) {
    memset(out_rgb, 0, w*h*3);
    double invA[6];
    if(!inv_similar(affine, invA)) return false;
    for(int y=0;y<h;y++){
        for(int x=0;x<w;x++){
            double nx = invA[0]*x + invA[1]*y + invA[2];
            double ny = invA[3]*x + invA[4]*y + invA[5];
            if(nx>=0 && nx<w-1 && ny>=0 && ny<h-1){
                int xi = (int)nx;
                int yi = (int)ny;
                int opos = (y*w + x)*3;
                int ipos = (yi*w + xi)*3;
                out_rgb[opos] = in_rgb[ipos];
                out_rgb[opos+1] = in_rgb[ipos+1];
                out_rgb[opos+2] = in_rgb[ipos+2];
            }
        }
    }
    return true;
}