static
gnb_length_t
gnb_il_get_band_parameters_len 
(
    band_parameters_t * p_band_parameters;
);

static
gnb_return_et
gnb_il_compose_band_parameters 
(
    UInt8 **pp_buffer,
    band_parameters_t * p_band_parameters
);

static
gnb_length_t
gnb_il_get_plmn_id_len 
(
    plmn_id_t * p_plmn_id;
);

static
gnb_return_et
gnb_il_compose_plmn_id 
(
    UInt8 **pp_buffer,
    plmn_id_t * p_plmn_id
);

static
gnb_length_t
gnb_il_get_octet_string_len 
(
    octet_string_t * p_octet_string;
);

static
gnb_return_et
gnb_il_compose_octet_string 
(
    UInt8 **pp_buffer,
    octet_string_t * p_octet_string
);

static
gnb_length_t
gnb_il_get_rf_parameters_len 
(
    rf_parameters_t * p_rf_parameters;
);

static
gnb_return_et
gnb_il_compose_rf_parameters 
(
    UInt8 **pp_buffer,
    rf_parameters_t * p_rf_parameters
);

static
gnb_length_t
gnb_il_get_device_config_len 
(
    device_config_t * p_device_config;
);

static
gnb_return_et
gnb_il_compose_device_config 
(
    UInt8 **pp_buffer,
    device_config_t * p_device_config
);
