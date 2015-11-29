typedef int64_t i64;

int width(i64 inum) {
  i64 num = inum < 0 ? -inum : inum;
  if (num < 10000000000) {
    if (num < 100000) {
      if (num < 10) {
	return 1;
      } else if (num < 100) {
	return 2;
      } else if (num < 1000) {
	return 3;
      } else if (num < 10000) {
	return 4;
      } else {
	return 5;
      }
    } else {
      if (num < 1000000) {
	return 6;
      } else if (num < 10000000) {
	return 7;
      } else if (num < 100000000) {
	return 8;
      } else {
	return 9;
      }
    }
  } else {
    if (num < 1000000000000000) {
      if (num < 10000000000) {
	return 10;
      } else if (num < 100000000000) {
	return 11;
      } else if (num < 1000000000000) {
	return 12;
      } else if (num < 10000000000000) {
	return 13;
      } else {
	return 14;
      } 
    } else {
      if (num < 1000000000000000) {
	return 15;
      } else if (num < 10000000000000000) {
	return 16;
      } else if (num < 100000000000000000) {
	return 17;
      } else if (num < 1000000000000000000) {
	return 18;
      } else {
	return 19;
      }
    }
  }
}
