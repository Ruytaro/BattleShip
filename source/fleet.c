#include "fleet.h"

uint8_t ship_sizes[] = {0, 0, 0, 0, 1, 1, 1, 1, 1, 2, 2, 3};

uint8_t fleet_size = sizeof(ship_sizes) / sizeof(ship_sizes[0]);

ship_t *fleet_init() {
  ship_t *fleet = (ship_t *)calloc(fleet_size, sizeof(ship_t));
  if (fleet == NULL) {
    exit(EXIT_FAILURE);
  }
  for (uint8_t i = 0; i < fleet_size; i++) {
    fleet[i] = *ship_init(i + 1, ship_sizes[i]);
  }
  return fleet;
}

void fleet_free(ship_t *fleet) {
  if (fleet == NULL) {
    return;
  }
  for (int i = 0; i < fleet_size; i++) {
    ship_free(&fleet[i]);
  }
  free(fleet);
  fleet = NULL;
}

void fleet_reset(ship_t *fleet) {
  for (int i = 0; i < fleet_size; i++) {
    ship_reset(&fleet[i]);
  }
}
