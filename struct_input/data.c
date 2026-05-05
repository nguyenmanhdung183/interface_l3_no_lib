
#define MAX_BANDS 8
#define MAX_OCTET_STRING_LEN 20

//[0] present (O/M) - indicates if the field is optional (O) or mandatory (M)
//[1] bitmask (0 is not present)
//[2] check bounds (H , B, N /OCTET_STRING )

//[3]  MIN  - if OCTET_STRING not present
//[4] MAX  - if OCTET_STRING not present

//[3] description - if OCTET_STRING is present, this field describes the type of OCTET_STRING (e.g., VARIABLE, FIXED, LIMITED_TILL_THE_END)

// Example enum
typedef enum
{
    BAND_1 = 0,
    BAND_3 = 1,
    BAND_7 = 2,
    BAND_20 = 3
} band_et;

/* ---------------------- Inner Struct ---------------------- */

typedef struct {
    UInt8 haha[10]; /*^ M, 0, OCTET_STRING, FIXED ^*/
    UInt16 hihi;
} dunglieu_t;

typedef struct
{
#define BAND_PARAM_BITMASK_OPTIONAL_PARAM_ID_PRESENT (1 << 0)
#define BAND_PARAM_BITMASK_OPTIONAL_PARAM_DATA_PRESENT (1 << 1)
    rrc_bitmask_t bitmask;               /*^ BITMASK ^*/
    UInt8 band_id; /*^ M, 0, H, 0, 3 ^*/ /*band_et*/
    UInt16 frequency; /*^ M, 0, B, 0, 6000 ^*/                                                                       
    UInt8 optional_param_id; /*^ O, BAND_PARAM_BITMASK_OPTIONAL_PARAM_ID_PRESENT, H, 0, 10 ^*/      
    UInt8 optional_param_data; /*^ O, BAND_PARAM_BITMASK_OPTIONAL_PARAM_DATA_PRESENT, B, 0, 255 ^*/ 
    dunglieu_t NHL[100] /*^ M, 0, OCTET_STRING, FIXED ^*/
} band_parameters_t;

/* ---------------------- Struct with OCTET STRING ---------------------- */
typedef struct
{
    UInt8 length_a; /*^ M, 0, B, 0, MAX_OCTET_STRING_LEN^*/                  // length of octet string
    UInt16 data_a[MAX_OCTET_STRING_LEN]; /*^ M, 0, OCTET_STRING, VARIABLE ^*/ /*^ length_a ^*/
} octet_string_t;



/* ---------------------- Middle Struct ---------------------- */
typedef struct 
{
    //UInt8 hehe;
    UInt8 plmn_count; /*^ M, 0, B, 0, MAX_OCTET_STRING_LEN^*/ // length of octet string
    UInt8 data[MAX_OCTET_STRING_LEN];                         /*^ M, 0, OCTET_STRING, VARIABLE ^*/
} plmn_id_t;
/* ---------------------- Top Struct ---------------------- */
typedef struct
{
#define DEVICE_CONFIG_BITMASK_EXTRA_DATA_PRESENT (1 << 0)
#define CONFIG_PRESENT (1 << 1)
    UInt16 bitmask;                                                        /*^ BITMASK ^*/
    UInt8 version;                                                         /*^ M, 0, B, 0, 255 ^*/
    rf_parameters_t rf_params;                                             /*^ M, 0, N, 0, 0 ^*/
    UInt8 extra_data_config; /*^ O, CONFIG_PRESENT, N, 0, 0 ^*/            // optional field
    octet_string_t extra_data[20];                                             /*^ O, DEVICE_CONFIG_BITMASK_EXTRA_DATA_PRESENT, OCTET_STRING, FIXED ^*/
    UInt16 band_count;                                                     /*^ M, 0, B, 0, MAX_COUNT^*/
    band_parameters_t band_data[100]; /*^ M, 0, OCTET_STRING, VARIABLE ^*/ /*^ band_count ^*/
    UInt8 list_id[80]; /*^ M, 0, OCTET_STRING, FIXED ^*/
    plmn_id_t plmn; /*^ M, 0, N, 0, 0 ^*/
} device_config_t;

typedef struct _rf_parameters_t
{
#define RF_PARAM_BITMASK_CONFIG_BLOB_PRESENT (1 << 0)
    rrc_bitmask_t bitmask;              /*^ BITMASK ^*/
    UInt16 id;                          /*^ M, 0, N, 0, 1000 ^*/
    UInt8 nmd[183];         /*^ M, 0, OCTET_STRING, FIXED, H, 0, 10 ^*/
    UInt8 num_bands;                    /*^ M, 0, B, 0, MAX_BANDS ^*/
    band_parameters_t bands[MAX_BANDS]; /*^ M, 0, OCTET_STRING, VARIABLE ^*/ /*^ num_bands ^*/
    octet_string_t config_blob[99];         /*^ O, RF_PARAM_BITMASK_CONFIG_BLOB_PRESENT, OCTET_STRING, FIXED ^*/
} rf_parameters_t;




typedef struct
{
    UInt32 ho_attempt; /*^ M, 0, N, 0, 0 ^*/
    UInt32 ho_succ;    /*^ M, 0, N, 0, 0 ^*/
    UInt32 ho_failure; /*^ M, 0, N, 0, 0 ^*/
} e2_report_mobility_ind_t;

typedef struct
{
    UInt8 is_ho_attempt; /*^ M, 0, B, 0, 1 ^*/
    UInt8 is_ho_succ;    /*^ M, 0, B, 0, 1 ^*/
    UInt8 is_ho_failure; /*^ M, 0, B, 0, 1 ^*/
} e2_report_mobility_req_t;

typedef struct
{
#define SUB_RIC_MOBILITY_REPORT_PRESENT 0x01

    UInt16 bitmask; /*^ BITMASK ^*/
    UInt32 ric_request_id; /*^ M, 0, N, 0, 0 ^*/
    UInt8 periodic;        /*^ M, 0, N, 0, 0 ^*/
    UInt32 report_period_ms; /*^ M, 0, N, 0, 0 ^*/
    e2_report_mobility_req_t report_mobility_req; /*^ O, SUB_RIC_MOBILITY_REPORT_PRESENT, N, 0, 0 ^*/
} rrc_e2sm_kpm_ric_sub_req_t;

typedef struct
{
#define IND_RIC_MOBILITY_REPORT_PRESENT 0x01

    UInt16 bitmask; /*^ BITMASK ^*/
    UInt32 ric_request_id; /*^ M, 0, N, 0, 0 ^*/
    e2_report_mobility_ind_t report_mobility_ind; /*^ O, IND_RIC_MOBILITY_REPORT_PRESENT, N, 0, 0 ^*/
} e2sm_rrc_ric_indication_t;