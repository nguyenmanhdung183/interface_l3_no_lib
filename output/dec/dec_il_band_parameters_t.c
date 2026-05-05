static
gnb_return_et
gnb_il_parse_band_parameters
(
    band_parameters_t * p_band_parameters,
    UInt8 * p_src,
    SInt32 length_left,
    SInt32 * p_length_read
){
    SInt32 length_read = 0;
    *p_length_read = 0;

    memset(p_band_parameters, 0, sizeof(band_parameters_t));

    /* This function parses band_parameters */
    GNB_CP_TRACE(GNB_DETAILEDALL, "dungnm26 - Parsing band_parameters");


/*----> rrc_bitmask_t ~ present_bitmask <----*/ 



    if (*p_length_read + (SInt32)sizeof(UInt16) > length_left)
    {
        GNB_CP_TRACE(GNB_WARNING, "dungnm26 - Incomming message damaged!");
        return GNB_FAILURE;
    }
    /* Parse/Unpack parameter of basic type */
    gnb_cp_unpack_UInt16(&p_band_parameters->present_bitmask, p_src + *p_length_read, "present_bitmask");
    *p_length_read += sizeof(p_band_parameters->present_bitmask);
    



        
        
    
        
                
        
 



/*----> UInt8 ~ band_id <----*/ 



    if (*p_length_read + (SInt32)sizeof(UInt8) > length_left)
    {
        GNB_CP_TRACE(GNB_WARNING, "dungnm26 - Incomming message damaged!");
        return GNB_FAILURE;
    }
    /* Parse/Unpack parameter of basic type */
    gnb_cp_unpack_UInt8(&p_band_parameters->band_id, p_src + *p_length_read, "band_id");
    *p_length_read += sizeof(p_band_parameters->band_id);
    



        
        
    
        
                
        
 
    /* Check for correct range [H - higher boundary] */
    if(p_band_parameters->band_id > 3)
    {
        GNB_CP_TRACE(GNB_WARNING, "dungnm26 - Parameter p_band_parameters->band_id should be less than or equal to 3"
            "Incorrect value: %d", p_band_parameters->band_id);
        return GNB_FAILURE;

    }


/*----> UInt16 ~ frequency <----*/ 



    if (*p_length_read + (SInt32)sizeof(UInt16) > length_left)
    {
        GNB_CP_TRACE(GNB_WARNING, "dungnm26 - Incomming message damaged!");
        return GNB_FAILURE;
    }
    /* Parse/Unpack parameter of basic type */
    gnb_cp_unpack_UInt16(&p_band_parameters->frequency, p_src + *p_length_read, "frequency");
    *p_length_read += sizeof(p_band_parameters->frequency);
    



        
        
    
        
                
        
 
    /* Check for correct range [B - both higher and lower boundary] */
    if(p_band_parameters->frequency < 0 || p_band_parameters->frequency > 6000) 
    {
        GNB_CP_TRACE(GNB_WARNING, "dungnm26 - Parameter p_band_parameters->frequency should be in range [ 0 - 6000]"
            "Incorrect value: %d", p_band_parameters->frequency);
        return GNB_FAILURE;

    }


/*----> UInt8 ~ optional_param_id <----*/ 


    /* Optional element */
    if(p_band_parameters->present_bitmask & BAND_PARAM_BITMASK_OPTIONAL_PARAM_ID_PRESENT)
    {

    if (*p_length_read + (SInt32)sizeof(UInt8) > length_left)
    {
        GNB_CP_TRACE(GNB_WARNING, "dungnm26 - Incomming message damaged!");
        return GNB_FAILURE;
    }
    /* Parse/Unpack parameter of basic type */
    gnb_cp_unpack_UInt8(&p_band_parameters->optional_param_id, p_src + *p_length_read, "optional_param_id");
    *p_length_read += sizeof(p_band_parameters->optional_param_id);
    



        
        
    
        
                
        
 
    /* Check for correct range [H - higher boundary] */
    if(p_band_parameters->optional_param_id > 10)
    {
        GNB_CP_TRACE(GNB_WARNING, "dungnm26 - Parameter p_band_parameters->optional_param_id should be less than or equal to 10"
            "Incorrect value: %d", p_band_parameters->optional_param_id);
        return GNB_FAILURE;

    }

    }

/*----> UInt8 ~ optional_param_data <----*/ 


    /* Optional element */
    if(p_band_parameters->present_bitmask & BAND_PARAM_BITMASK_OPTIONAL_PARAM_DATA_PRESENT)
    {

    if (*p_length_read + (SInt32)sizeof(UInt8) > length_left)
    {
        GNB_CP_TRACE(GNB_WARNING, "dungnm26 - Incomming message damaged!");
        return GNB_FAILURE;
    }
    /* Parse/Unpack parameter of basic type */
    gnb_cp_unpack_UInt8(&p_band_parameters->optional_param_data, p_src + *p_length_read, "optional_param_data");
    *p_length_read += sizeof(p_band_parameters->optional_param_data);
    



        
        
    
        
                
        
 
    /* Check for correct range [B - both higher and lower boundary] */
    if(p_band_parameters->optional_param_data < 0 || p_band_parameters->optional_param_data > 255) 
    {
        GNB_CP_TRACE(GNB_WARNING, "dungnm26 - Parameter p_band_parameters->optional_param_data should be in range [ 0 - 255]"
            "Incorrect value: %d", p_band_parameters->optional_param_data);
        return GNB_FAILURE;

    }

    }

/*----> dunglieu_t ~ NHL <----*/ 






        
        
    
        
                
    /* Parse of OCTET_STRING FIXED of IEs */
    {
        //:))))
        gnb_counter_t loop;
        for(loop = 0; loop < ARRSIZE(p_band_parameters->NHL); loop++)
        {
            if(GNB_FAILURE == gnb_il_parse_dunglieu(
                &p_band_parameters->NHL[loop], 
                p_src + *p_length_read, 
                length_left - *p_length_read,
                &length_read))
            {
                return GNB_FAILURE;
            }
            *p_length_read += length_read;
        }
    }
        
 



/*----> manhdung_t ~ MD <----*/ 




    /* Parse/Unpack IE */
    if(GNB_FAILURE == gnb_il_parse_manhdung(
        &p_band_parameters->MD, 
        p_src + *p_length_read, 
        length_left - *p_length_read,
        &length_read))
    {
        return GNB_FAILURE;
    }

    *p_length_read += length_read;


        
        
    
        
                
        
 



/* final check */
    if(*p_length_read > length_left)
    {
        GNB_CP_TRACE(GNB_WARNING, "dungnm26 - Incomming message damaged!");
        return GNB_FAILURE;
    }

    return GNB_SUCCESS;
}



