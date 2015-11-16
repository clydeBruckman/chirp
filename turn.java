public void turn (float rad, float speed) {
	float portion = rad * 9;
	float rad_wheel = (portion/(8*pi));
	float encoder_target = rad_wheel * EREVOLUTIONS;

	while(drive_left_front.encoder_count < encoder_target) {
		drive_left_front = drive_left_back = Math.signum(rad)*speed;
		drive_right_front = drive_right_back = -1*Math.signum(rad)*speed;
	}
	drive_left_front = drive_left_back = drive_right_front = drive_right_back = 0;
	// call universal "reset encoders" function.
}

