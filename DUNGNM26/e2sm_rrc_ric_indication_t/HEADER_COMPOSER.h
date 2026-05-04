static
gnb_length_t
gnb_il_get_e2_report_mobility_ind_len 
(
    e2_report_mobility_ind_t * p_e2_report_mobility_ind;
);


static
gnb_return_et
gnb_il_compose_e2_report_mobility_ind 
(
    UInt8 **pp_buffer,
    e2_report_mobility_ind_t * p_e2_report_mobility_ind
);


static
gnb_length_t
gnb_il_get_e2sm_rrc_ric_indication_len 
(
    e2sm_rrc_ric_indication_t * p_e2sm_rrc_ric_indication;
);


static
gnb_return_et
gnb_il_compose_e2sm_rrc_ric_indication 
(
    UInt8 **pp_buffer,
    e2sm_rrc_ric_indication_t * p_e2sm_rrc_ric_indication
);


