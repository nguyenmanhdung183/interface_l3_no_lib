static
gnb_length_t
gnb_il_get_e2_report_mobility_req_len 
(
    e2_report_mobility_req_t * p_e2_report_mobility_req;
);


static
gnb_return_et
gnb_il_compose_e2_report_mobility_req 
(
    UInt8 **pp_buffer,
    e2_report_mobility_req_t * p_e2_report_mobility_req
);


static
gnb_length_t
gnb_il_get_rrc_e2sm_kpm_ric_sub_req_len 
(
    rrc_e2sm_kpm_ric_sub_req_t * p_rrc_e2sm_kpm_ric_sub_req;
);


static
gnb_return_et
gnb_il_compose_rrc_e2sm_kpm_ric_sub_req 
(
    UInt8 **pp_buffer,
    rrc_e2sm_kpm_ric_sub_req_t * p_rrc_e2sm_kpm_ric_sub_req
);


