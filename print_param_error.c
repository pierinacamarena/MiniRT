#include "check_params.h"

void	print_param_error(int error)
{
	if (error != 0)
		printf("Error\n");
	if ((error & COORD_LIMIT) != 0)
		printf("%f <= [coordinate] <= %f\n", L_LIMIT, U_LIMIT);
	if ((error & ORIENT_LIMIT) != 0)
		printf("-1.0 <= [orientation] <= 1.0)\n");
	if ((error & LIGHT_RATIO_LIMIT) != 0)
		printf("0.0 <= [intensity] <= 1.0\n");
	if ((error & FOV_LIMIT) != 0)
		printf("0 < [FOV] < 180\n");
	if ((error & RGB_LIMIT) != 0)
		printf("0 <= [RGB] <= 255\n");
	if ((error & DIAMETER_LIMIT) != 0)
		printf("0 < [diameter] <= %f\n", U_LIMIT);
	if ((error & HEIGHT_LIMIT) != 0)
		printf("0 < [height] <= %f\n", U_LIMIT);
	if ((error & MISSING_CAM) != 0)
		printf("Missing camera\n");
	if ((error & MISSING_LIGHT) != 0)
		printf("Missing light\n");
	if ((error & MISSING_AMBIENT) != 0)
		printf("Missing ambient\n");
}
