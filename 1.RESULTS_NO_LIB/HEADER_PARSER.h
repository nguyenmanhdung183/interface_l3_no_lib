static 
gnb_return_et
gnb_il_parse_octet_string 
(
    octet_string_t * p_octet_string,
    UInt8 * p_src,
    SInt32 length_left,
    SInt32 * p_length_read
);

static 
gnb_return_et
gnb_il_parse_plmn_id 
(
    plmn_id_t * p_plmn_id,
    UInt8 * p_src,
    SInt32 length_left,
    SInt32 * p_length_read
);

static 
gnb_return_et
gnb_il_parse_dunglieu 
(
    dunglieu_t * p_dunglieu,
    UInt8 * p_src,
    SInt32 length_left,
    SInt32 * p_length_read
);

static 
gnb_return_et
gnb_il_parse_band_parameters 
(
    band_parameters_t * p_band_parameters,
    UInt8 * p_src,
    SInt32 length_left,
    SInt32 * p_length_read
);

static 
gnb_return_et
gnb_il_parse_rf_parameters 
(
    rf_parameters_t * p_rf_parameters,
    UInt8 * p_src,
    SInt32 length_left,
    SInt32 * p_length_read
);

static 
gnb_return_et
gnb_il_parse_device_config 
(
    device_config_t * p_device_config,
    UInt8 * p_src,
    SInt32 length_left,
    SInt32 * p_length_read
);
