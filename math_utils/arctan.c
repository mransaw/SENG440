#include "linear_approx.h"
#include <stdio.h>
#include <math.h>

void generate_linear_approximation(double MIN, double MAX, double INC) {
    int intervals = (MAX - MIN) / INC;
    double slopes[intervals];
    double intercepts[intervals];
    double lower_X = MIN;
    double upper_X = MIN + INC;
    int i = 0;
    for (double lower_X = MIN; upper_X <= MAX; lower_X += INC) {
        slopes[i] = (atan(upper_X) - atan(lower_X)) / (upper_X - lower_X);
        intercepts[i] = 0.5 * (atan(upper_X) + atan(lower_X)) - (slopes[i] * (upper_X + lower_X) * 0.5);
        if (lower_X == MIN) {
            printf("if (%d <= x && x< %d) { return (%d * x) + %d; }\n", (int)(lower_X * (1 << SF_ATAN_IN)), (int)(upper_X * (1 << SF_ATAN_IN)), (int)(slopes[i] * (1 << SF_ATAN_IN)/ M_PI), (int)(intercepts[i] * (1 << SF_ATAN_IN)/ M_PI));
        } else {
            printf("else if (%d <= x && x< %d) { return (%d * x) + %d; }\n", (int)(lower_X * (1 << SF_ATAN_IN)), (int)(upper_X * (1 << SF_ATAN_IN)), (int)(slopes[i] * (1 << SF_ATAN_IN)/ M_PI), (int)(intercepts[i] * (1 << SF_ATAN_IN)/ M_PI));
        }
        upper_X += INC;
        ++i;
    }
}

void eval_error() {
    double max_error = 0;
    double error = 0;
    double inc = 0.001;
    for (double x = -1.0; x < 1.0; x += inc) {
        error = (d_arctan(x) - atan(x));
        printf("x = %f, d_arctan(x) = %f, atan(x) = %f, diff error: %f\n", x, d_arctan(x), atan(x), (d_arctan(x) - atan(x)));
        if (error > max_error) {
            max_error = error;
        }
    }
    for (double x = -8192; x <= 8192; x++) {
        error = (d_arctan(x) - atan(x));
        printf("x = %f, d_arctan(x) = %f, atan(x) = %f, diff error: %f\n", x, d_arctan(x), atan(x), (d_arctan(x) - atan(x)));
        if (error > max_error) {
            max_error = error;
        }
    }
    printf("Max error: %f\n", max_error);
}

int arctan(int X) {
    //generate_linear_approximation(-1.0, 1.0, 0.1);
    //generate_linear_approximation(-10.0, 10.0, 1);
    //int min_element = -(1 << (32-SF_IN)),
    //max_element = 1 << (32-SF_IN);   
    //generate_linear_approximation(min_element, max_element, 10000);
    //eval_error();
    //double x = ((double)X) / ((double)(1 << SF_ATAN_IN));
    //double result = (d_arctan(x) * (1 << SF_ATAN_OUT) / M_PI) - 1;
    //return result;
    return int_arctan(X);
}

int int_arctan(int X) {
    int x = X;
    if ((-1 * (1 << SF_ATAN_IN)) <= x && x <= (1 * (1 << SF_ATAN_IN))) {
        if (-16384 <= x && x< -14745) { return (2742 * x) + -1353; }
        else if (-14745 <= x && x< -13107) { return (3028 * x) + -1095; }
        else if (-13107 <= x && x< -11468) { return (3338 * x) + -848; }
        else if (-11468 <= x && x< -9830) { return (3666 * x) + -618; }
        else if (-9830 <= x && x< -8192) { return (4003 * x) + -416; }
        else if (-8192 <= x && x< -6553) { return (4335 * x) + -250; }
        else if (-6553 <= x && x< -4915) { return (4644 * x) + -126; }
        else if (-4915 <= x && x< -3276) { return (4905 * x) + -48; }
        else if (-3276 <= x && x< -1638) { return (5096 * x) + -10; }
        else if (-1638 <= x && x< 0) { return (5197 * x) + 0; }
        else if (0 <= x && x< 1638) { return (5197 * x) + 0; }
        else if (1638 <= x && x< 3276) { return (5096 * x) + 10; }
        else if (3276 <= x && x< 4915) { return (4905 * x) + 48; }
        else if (4915 <= x && x< 6553) { return (4644 * x) + 126; }
        else if (6553 <= x && x< 8191) { return (4335 * x) + 250; }
        else if (8191 <= x && x< 9830) { return (4003 * x) + 416; }
        else if (9830 <= x && x< 11468) { return (3666 * x) + 618; }
        else if (11468 <= x && x< 13107) { return (3338 * x) + 848; }
        else if (13107 <= x && x< 14745) { return (3028 * x) + 1095; }
        else if (14745 <= x && x< 16383) { return (2742 * x) + 1353; }
        else { return 0;}
    }
    else if ((-10 * (1 << SF_ATAN_IN)) <= x && x <= (10 * (1 << SF_ATAN_IN))) {
        if (-163840 <= x && x< -147456) { return (57 * x) + -7099; }
        else if (-147456 <= x && x< -131072) { return (71 * x) + -6971; }
        else if (-131072 <= x && x< -114688) { return (91 * x) + -6811; }
        else if (-114688 <= x && x< -98304) { return (121 * x) + -6603; }
        else if (-98304 <= x && x< -81920) { return (168 * x) + -6321; }
        else if (-81920 <= x && x< -65536) { return (248 * x) + -5921; }
        else if (-65536 <= x && x< -49152) { return (400 * x) + -5312; }
        else if (-49152 <= x && x< -32768) { return (740 * x) + -4293; }
        else if (-32768 <= x && x< -16384) { return (1677 * x) + -2418; }
        else if (-16384 <= x && x< 0) { return (4096 * x) + 0; }
        else if (0 <= x && x< 16384) { return (4096 * x) + 0; }
        else if (16384 <= x && x< 32768) { return (1677 * x) + 2418; }
        else if (32768 <= x && x< 49152) { return (740 * x) + 4293; }
        else if (49152 <= x && x< 65536) { return (400 * x) + 5312; }
        else if (65536 <= x && x< 81920) { return (248 * x) + 5921; }
        else if (81920 <= x && x< 98304) { return (168 * x) + 6321; }
        else if (98304 <= x && x< 114688) { return (121 * x) + 6603; }
        else if (114688 <= x && x< 131072) { return (91 * x) + 6811; }
        else if (131072 <= x && x< 147456) { return (71 * x) + 6971; }
        else if (147456 <= x && x< 163840) { return (57 * x) + 7099; }
        else { return 0;}
    }
    else { 
        if (-2147483648 <= x && x< -2147483648) { return (0 * x) + -8191; }
        else if (-2147483648 <= x && x< -2147483648) { return (0 * x) + -8191; }
        else if (-2147483648 <= x && x< -2147483648) { return (0 * x) + -8191; }
        else if (-2147483648 <= x && x< -2147483648) { return (0 * x) + -8191; }
        else if (-2147483648 <= x && x< -2147483648) { return (0 * x) + -8191; }
        else if (-2147483648 <= x && x< -2147483648) { return (0 * x) + -8191; }
        else if (-2147483648 <= x && x< -2147483648) { return (0 * x) + -8191; }
        else if (-2147483648 <= x && x< -2147483648) { return (0 * x) + -8191; }
        else if (-2147483648 <= x && x< -2147483648) { return (0 * x) + -8191; }
        else if (-2147483648 <= x && x< -2147483648) { return (0 * x) + -8191; }
        else if (-2147483648 <= x && x< -2147483648) { return (0 * x) + -8191; }
        else if (-2147483648 <= x && x< -2147483648) { return (0 * x) + -8191; }
        else if (-2147483648 <= x && x< -2147483648) { return (0 * x) + -8191; }
        else if (-2147483648 <= x && x< -2001207296) { return (0 * x) + -8191; }
        else if (-2001207296 <= x && x< -1837367296) { return (0 * x) + -8191; }
        else if (-1837367296 <= x && x< -1673527296) { return (0 * x) + -8191; }
        else if (-1673527296 <= x && x< -1509687296) { return (0 * x) + -8191; }
        else if (-1509687296 <= x && x< -1345847296) { return (0 * x) + -8191; }
        else if (-1345847296 <= x && x< -1182007296) { return (0 * x) + -8191; }
        else if (-1182007296 <= x && x< -1018167296) { return (0 * x) + -8191; }
        else if (-1018167296 <= x && x< -854327296) { return (0 * x) + -8191; }
        else if (-854327296 <= x && x< -690487296) { return (0 * x) + -8191; }
        else if (-690487296 <= x && x< -526647296) { return (0 * x) + -8191; }
        else if (-526647296 <= x && x< -362807296) { return (0 * x) + -8191; }
        else if (-362807296 <= x && x< -198967296) { return (0 * x) + -8191; }
        else if (-198967296 <= x && x< -35127296) { return (0 * x) + -8189; }
        else if (-35127296 <= x && x< 128712704) { return (1 * x) + -4677; }
        else { return 8191;}
    }
}

double d_arctan(double x) {
    if (-1 <= x && x <= 1.0) {
        if (-1.000000 <= x && x< -0.900000) { return (0.525831 * x) + -0.259568; }
        else if (-0.900000 <= x && x< -0.800000) { return (0.580742 * x) + -0.210148; }
        else if (-0.800000 <= x && x< -0.700000) { return (0.640150 * x) + -0.162621; }
        else if (-0.700000 <= x && x< -0.600000) { return (0.703065 * x) + -0.118581; }
        else if (-0.600000 <= x && x< -0.500000) { return (0.767719 * x) + -0.079788; }
        else if (-0.500000 <= x && x< -0.400000) { return (0.831412 * x) + -0.047941; }
        else if (-0.400000 <= x && x< -0.300000) { return (0.890496 * x) + -0.024308; }
        else if (-0.300000 <= x && x< -0.200000) { return (0.940612 * x) + -0.009273; }
        else if (-0.200000 <= x && x< -0.100000) { return (0.977269 * x) + -0.001942; }
        else if (-0.100000 <= x && x< -0.000000) { return (0.996687 * x) + 0.000000; }
        else if (-0.000000 <= x && x< 0.100000) { return (0.996687 * x) + 0.000000; }
        else if (0.100000 <= x && x< 0.200000) { return (0.977269 * x) + 0.001942; }
        else if (0.200000 <= x && x< 0.300000) { return (0.940612 * x) + 0.009273; }
        else if (0.300000 <= x && x< 0.400000) { return (0.890496 * x) + 0.024308; }
        else if (0.400000 <= x && x< 0.500000) { return (0.831412 * x) + 0.047941; }
        else if (0.500000 <= x && x< 0.600000) { return (0.767719 * x) + 0.079788; }
        else if (0.600000 <= x && x< 0.700000) { return (0.703065 * x) + 0.118581; }
        else if (0.700000 <= x && x< 0.800000) { return (0.640150 * x) + 0.162621; }
        else if (0.800000 <= x && x< 0.900000) { return (0.580742 * x) + 0.210148; }
        else if (0.900000 <= x && x< 1.000000) { return (0.525831 * x) + 0.259568; }
        else { return 0; }
    }
    else if (-10.0 <= x && x <= 10.0) {
        if (-10.000000 <= x && x< -9.000000) { return (0.010989 * x) + -1.361242; }
        else if (-9.000000 <= x && x< -8.000000) { return (0.013698 * x) + -1.336859; }
        else if (-8.000000 <= x && x< -7.000000) { return (0.017542 * x) + -1.306105; }
        else if (-7.000000 <= x && x< -6.000000) { return (0.023252 * x) + -1.266138; }
        else if (-6.000000 <= x && x< -5.000000) { return (0.032247 * x) + -1.212166; }
        else if (-5.000000 <= x && x< -4.000000) { return (0.047583 * x) + -1.135485; }
        else if (-4.000000 <= x && x< -3.000000) { return (0.076772 * x) + -1.018730; }
        else if (-3.000000 <= x && x< -2.000000) { return (0.141897 * x) + -0.823355; }
        else if (-2.000000 <= x && x< -1.000000) { return (0.321751 * x) + -0.463648; }
        else if (-1.000000 <= x && x< 0.000000) { return (0.785398 * x) + 0.000000; }
        else if (0.000000 <= x && x< 1.000000) { return (0.785398 * x) + 0.000000; }
        else if (1.000000 <= x && x< 2.000000) { return (0.321751 * x) + 0.463648; }
        else if (2.000000 <= x && x< 3.000000) { return (0.141897 * x) + 0.823355; }
        else if (3.000000 <= x && x< 4.000000) { return (0.076772 * x) + 1.018730; }
        else if (4.000000 <= x && x< 5.000000) { return (0.047583 * x) + 1.135485; }
        else if (5.000000 <= x && x< 6.000000) { return (0.032247 * x) + 1.212166; }
        else if (6.000000 <= x && x< 7.000000) { return (0.023252 * x) + 1.266138; }
        else if (7.000000 <= x && x< 8.000000) { return (0.017542 * x) + 1.306105; }
        else if (8.000000 <= x && x< 9.000000) { return (0.013698 * x) + 1.336859; }
        else if (9.000000 <= x && x< 10.000000) { return (0.010989 * x) + 1.361242; }
        else { return 0; }
    }
    else {
        if (-262144.000000 <= x && x< -252144.000000) { return (0.000000 * x) + -1.570789; }
        else if (-252144.000000 <= x && x< -242144.000000) { return (0.000000 * x) + -1.570788; }
        else if (-242144.000000 <= x && x< -232144.000000) { return (0.000000 * x) + -1.570788; }
        else if (-232144.000000 <= x && x< -222144.000000) { return (0.000000 * x) + -1.570788; }
        else if (-222144.000000 <= x && x< -212144.000000) { return (0.000000 * x) + -1.570787; }
        else if (-212144.000000 <= x && x< -202144.000000) { return (0.000000 * x) + -1.570787; }
        else if (-202144.000000 <= x && x< -192144.000000) { return (0.000000 * x) + -1.570786; }
        else if (-192144.000000 <= x && x< -182144.000000) { return (0.000000 * x) + -1.570786; }
        else if (-182144.000000 <= x && x< -172144.000000) { return (0.000000 * x) + -1.570785; }
        else if (-172144.000000 <= x && x< -162144.000000) { return (0.000000 * x) + -1.570784; }
        else if (-162144.000000 <= x && x< -152144.000000) { return (0.000000 * x) + -1.570784; }
        else if (-152144.000000 <= x && x< -142144.000000) { return (0.000000 * x) + -1.570783; }
        else if (-142144.000000 <= x && x< -132144.000000) { return (0.000000 * x) + -1.570782; }
        else if (-132144.000000 <= x && x< -122144.000000) { return (0.000000 * x) + -1.570781; }
        else if (-122144.000000 <= x && x< -112144.000000) { return (0.000000 * x) + -1.570779; }
        else if (-112144.000000 <= x && x< -102144.000000) { return (0.000000 * x) + -1.570778; }
        else if (-102144.000000 <= x && x< -92144.000000) { return (0.000000 * x) + -1.570776; }
        else if (-92144.000000 <= x && x< -82144.000000) { return (0.000000 * x) + -1.570773; }
        else if (-82144.000000 <= x && x< -72144.000000) { return (0.000000 * x) + -1.570770; }
        else if (-72144.000000 <= x && x< -62144.000000) { return (0.000000 * x) + -1.570766; }
        else if (-62144.000000 <= x && x< -52144.000000) { return (0.000000 * x) + -1.570761; }
        else if (-52144.000000 <= x && x< -42144.000000) { return (0.000000 * x) + -1.570753; }
        else if (-42144.000000 <= x && x< -32144.000000) { return (0.000000 * x) + -1.570741; }
        else if (-32144.000000 <= x && x< -22144.000000) { return (0.000000 * x) + -1.570720; }
        else if (-22144.000000 <= x && x< -12144.000000) { return (0.000000 * x) + -1.570669; }
        else if (-12144.000000 <= x && x< -2144.000000) { return (0.000000 * x) + -1.570248; }
        else if (-2144.000000 <= x && x< 7856.000000) { return (0.000314 * x) + -0.896900; }
        else if (7856.000000 <= x && x< 17856.000000) { return (0.000000 * x) + 1.570613; }
        else if (17856.000000 <= x && x< 27856.000000) { return (0.000000 * x) + 1.570704; }
        else if (27856.000000 <= x && x< 37856.000000) { return (0.000000 * x) + 1.570734; }
        else if (37856.000000 <= x && x< 47856.000000) { return (0.000000 * x) + 1.570749; }
        else if (47856.000000 <= x && x< 57856.000000) { return (0.000000 * x) + 1.570758; }
        else if (57856.000000 <= x && x< 67856.000000) { return (0.000000 * x) + 1.570764; }
        else if (67856.000000 <= x && x< 77856.000000) { return (0.000000 * x) + 1.570769; }
        else if (77856.000000 <= x && x< 87856.000000) { return (0.000000 * x) + 1.570772; }
        else if (87856.000000 <= x && x< 97856.000000) { return (0.000000 * x) + 1.570775; }
        else if (97856.000000 <= x && x< 107856.000000) { return (0.000000 * x) + 1.570777; }
        else if (107856.000000 <= x && x< 117856.000000) { return (0.000000 * x) + 1.570779; }
        else if (117856.000000 <= x && x< 127856.000000) { return (0.000000 * x) + 1.570780; }
        else if (127856.000000 <= x && x< 137856.000000) { return (0.000000 * x) + 1.570781; }
        else if (137856.000000 <= x && x< 147856.000000) { return (0.000000 * x) + 1.570782; }
        else if (147856.000000 <= x && x< 157856.000000) { return (0.000000 * x) + 1.570783; }
        else if (157856.000000 <= x && x< 167856.000000) { return (0.000000 * x) + 1.570784; }
        else if (167856.000000 <= x && x< 177856.000000) { return (0.000000 * x) + 1.570785; }
        else if (177856.000000 <= x && x< 187856.000000) { return (0.000000 * x) + 1.570785; }
        else if (187856.000000 <= x && x< 197856.000000) { return (0.000000 * x) + 1.570786; }
        else if (197856.000000 <= x && x< 207856.000000) { return (0.000000 * x) + 1.570786; }
        else if (207856.000000 <= x && x< 217856.000000) { return (0.000000 * x) + 1.570787; }
        else if (217856.000000 <= x && x< 227856.000000) { return (0.000000 * x) + 1.570787; }
        else if (227856.000000 <= x && x< 237856.000000) { return (0.000000 * x) + 1.570788; }
        else if (237856.000000 <= x && x< 247856.000000) { return (0.000000 * x) + 1.570788; }
        else if (247856.000000 <= x && x< 257856.000000) { return (0.000000 * x) + 1.570788; }
        else {
            return 0;
        }
        
    }
    return 0;
}