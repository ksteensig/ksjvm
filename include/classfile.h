#pragma once

#include <stdint.h>

struct cp_info;
struct field_info;
struct method_info;
struct attribute_info;

/* Overall JVM class file structure */
struct ClassFile {
  uint32_t magic_number;
  uint16_t minor_version;
  uint16_t major_version;
  
  uint16_t constant_pool_count;
  struct cp_info **cp_info;
  
  uint16_t access_flags;
  uint16_t this_class;
  uint16_t super_class;

  uint16_t interfaces_count;
  uint16_t *interfaces;

  uint16_t field_count;
  struct field_info *field;
  
  uint16_t methods_count;
  struct MethodInfo *methods;
  
  uint16_t attributes_count;
  struct AttributeInfo *attributes;
};

typedef enum {
	      CONSTANT_Class = 7,
	      CONSTANT_Fieldref = 9,
	      CONSTANT_Methodref = 10,
	      CONSTANT_InterfaceMethodref = 11,
	      CONSTANT_String = 8,
	      CONSTANT_Integer = 3,
	      CONSTANT_Float = 4,
	      CONSTANT_Long = 5,
	      CONSTANT_Double = 6,
	      CONSTANT_NameAndType = 12,
	      CONSTANT_Utf8 = 1,
	      CONSTANT_MethodHandle = 15,
	      CONSTANT_MethodType = 16,
	      CONSTANT_InvokeDynamic = 18,
} Constant_Type_tag;


/* Only used for typecasting other Info types to */
struct cp_info {
  Constant_Type_tag tag;
};

struct CONSTANT_Class_info {
  Constant_Type_tag tag;
  uint16_t name_index;
};

struct CONSTANT_Fieldref_info {
  Constant_Type_tag tag;
  uint16_t class_index;
  uint16_t name_and_type_index;
};

struct CONSTANT_Methodref_info {
  Constant_Type_tag tag;
  uint16_t class_index;
  uint16_t name_and_type_index;
};

struct CONSTANT_InterfaceMethodref_info {
  Constant_Type_tag tag;
  uint16_t class_index;
  uint16_t name_and_type_index;
};

struct CONSTANT_String_info {
  Constant_Type_tag tag;
  uint16_t string_index;
};

struct CONSTANT_Integer_info {
  Constant_Type_tag tag;
  uint32_t bytes;
};

struct CONSTANT_Float_info {
  Constant_Type_tag tag;
  uint32_t bytes;
};

struct CONSTANT_Long_info {
  Constant_Type_tag tag;
  uint32_t high_bytes;
  uint32_t low_bytes;
};

struct CONSTANT_Double_info {
  Constant_Type_tag tag;
  uint32_t high_bytes;
  uint32_t low_bytes;
};

struct CONSTANT_NameAndType_info {
  Constant_Type_tag tag;
  uint16_t name_index;
  uint16_t descriptor_index;
};

struct CONSTANT_Utf8_info {
    Constant_Type_tag tag;
    uint16_t length;
    uint8_t *bytes;
};

struct CONSTANT_MethodHandle_info {
    Constant_Type_tag tag;
    uint8_t reference_kind;
    uint16_t reference_index;
};

struct CONSTANT_MethodType_info {
  Constant_Type_tag tag;
  uint16_t descriptor_index;
};

struct CONSTANT_InvokeDynamic_info {
  Constant_Type_tag tag;
  uint16_t bootstrap_method_attr_index;
  uint16_t name_and_type_index;
};

typedef enum {
	      FIELD_ACC_PUBLIC = 0x0001,
	      FIELD_ACC_PRIVATE = 0x0002,
	      FIELD_ACC_PROTECTED = 0x004,
	      FIELD_ACC_STATIC = 0x0008,
	      FIELD_ACC_FINAL = 0x0010,
	      FIELD_ACC_VOLATILE = 0x0040,
	      FIELD_ACC_TRANSIENT = 0x0080,
	      FIELD_ACC_SYNTHETIC = 0x1000,
	      FIELD_ACC_ENUM = 0x4000,
} Field_Access_flags;

struct field_info {
  Field_Access_flags access_flags;
  uint16_t name_index;
  uint16_t descriptor_index;
  uint16_t attributes_count;
  struct attribute_info *attributes;
};



typedef enum {
	      METHOD_ACC_PUBLIC = 0x0001,
	      METHOD_ACC_PRIVATE = 0x0002,
	      METHOD_ACC_PROTECTED = 0x004,
	      METHOD_ACC_STATIC = 0x0008,
	      METHOD_ACC_FINAL = 0x0010,
	      METHOD_ACC_SYNCHRONIZED = 0x0020,
	      METHOD_ACC_BRIDGE = 0x0040,
	      METHOD_ACC_VARGARGS = 0x0080,
	      METHOD_ACC_NATIVE = 0x0100,
	      METHOD_ACC_ABSTRACT = 0x0400,
	      METHOD_ACC_STRICT = 0x0800,
	      METHOD_ACC_SYNTHETIC = 0x1000,
} Method_Access_flags;
  
struct method_info {
  Method_Access_flags access_flags;
  uint16_t name_index;
  uint16_t descriptor_index;
  uint16_t attributes_count;
  struct attribute_info *attributes;
};


struct attribute_info {
  uint16_t attribute_name_index;
  uint32_t attribute_length;
};

struct ConstantValue_attribute {
  uint16_t attribute_name_index;
  uint32_t attribute_length;

  /* can refer to a long, float, double, int and string */
  uint16_t constantvalue_index;
};

struct exception_table_entry {
  uint16_t start_pc;
  uint16_t end_pc;
  uint16_t handler_pc;

  // must refer to a CONSTANT_Class_info
  uint16_t catch_type;
};

struct Code_attribute {
  uint16_t attribute_name_index;
  uint32_t attribute_length;
  uint16_t max_stack;
  uint16_t max_locals;
  uint32_t code_length;
  uint8_t *code;
  uint16_t exception_table_length;
  struct exception_table_entry *exception_table;
  uint16_t attributes_count;
  struct attribute_info *attributes;
};

struct Top_variable_info {
  uint8_t tag; /* 0 */
};

struct Integer_variable_info {
  uint8_t tag; /* 1 */
};

struct Float_variable_info {
  uint8_t tag; /* 2 */
};

struct Long_variable_info {
  uint8_t tag; /* 4 */
};

struct Double_variable_info {
  uint8_t tag; /* 3 */
};

struct Null_variable_info {
  uint8_t tag; /* 5 */
};

struct UninitializedThis_variable_info {
  uint8_t tag; /* 6 */
};

struct Object_variable_info {
  uint8_t tag; /* 7 */
  uint16_t cpool_index;
};

struct Uninitialized_variable_info {
  uint8_t tag; /* 8 */
  uint16_t offset;
};

union verification_type_info {
    struct Top_variable_info Top_variable_info;
    struct Integer_variable_info Integer_variable_info;
    struct Float_variable_info Float_variable_info;
    struct Long_variable_info Long_variable_info;
    struct Double_variable_info Double_variable_info;
    struct Null_variable_info Null_variable_info;
    struct UninitializedThis_variable_info UninitializedThis_variable_info;
    struct Object_variable_info Object_variable_info;
    struct Uninitialized_variable_info Uninitialized_variable_info;
};

struct same_frame {
  uint8_t frame_type; /* 0-63 */
};

struct same_locals_1_stack_item_frame {
  uint8_t frame_type; /* 64-127 */
  union verification_type_info *stack; /* [1] */
};

struct same_locals_1_stack_item_frame_extended {
  uint8_t frame_type; /* 247 */
  uint16_t offset_delta;
  union verification_type_info stack; /* [1] */
};

struct chop_frame {
  uint8_t frame_type; /* 248-250 */
  uint16_t offset_delta;
};

struct same_frame_extended {
  uint8_t frame_type; /* 251 */
  uint16_t offset_delta;
};

struct append_frame {
  uint8_t frame_type; /* 252-254 */
  uint16_t offset_delta;
  union verification_type_info *locals; /* [frame_type - 251] */;
};

struct full_frame {
    uint8_t frame_type; /* 255 */
    uint16_t offset_delta;
    uint16_t number_of_locals;
    union verification_type_info *locals;
    uint16_t number_of_stack_items;
    union verification_type_info *stack;
};

union stack_map_frame {
    struct same_frame same_frame;
    struct same_locals_1_stack_item_frame same_locals_1_stack_item_frame;
    struct same_locals_1_stack_item_frame_extended same_locals_1_stack_item_frame_extended;
    struct chop_frame chop_frame;
    struct same_frame_extended same_frame_extended;
    struct append_frame append_frame;
    struct full_frame full_frame;
};

struct StackMapTable_attribute {
  uint16_t attribute_name_index;
  uint32_t attribute_length;
  uint16_t number_of_entries;
  union stack_map_frame *entries;
};

struct Exceptions_attribute {
  uint16_t attribute_name_index;
  uint32_t attribute_length;
  uint32_t number_of_exceptions;
  uint16_t *exception_index_table; /* [number_of_exception] */
};


typedef enum {
	      INNER_CLASS_ACC_PUBLIC = 0x0001,
	      INNER_CLASS_ACC_PRIVATE = 0x0002,
	      INNER_CLASS_ACC_PROTECTED = 0x004,
	      INNER_CLASS_ACC_STATIC = 0x0008,
	      INNER_CLASS_ACC_FINAL = 0x0010,
	      INNER_CLASS_ACC_INTERFACE = 0x0200,
	      INNER_CLASS_ACC_ABSTRACT = 0x0400,
	      INNER_CLASS_ACC_SYNTHETIC = 0x1000,
	      INNER_CLASS_ACC_ANNOTATION = 0x2000,
	      INNER_CLASS_ACC_ENUM = 0x4000,
} InnerClass_Access_flags;

struct inner_class {
  uint16_t inner_class_info_index;
  uint16_t outer_class_info_index;
  uint16_t inner_name_index;
  InnerClass_Access_flags inner_class_access_flags;
};

struct InnerClasses_attribute {
  uint16_t attribute_name_index;
  uint32_t attribute_length;
  uint16_t number_of_classes;
  struct inner_class *classes;
};


struct EnclosingMethod_attribute {
  uint16_t attribute_name_index;
  uint32_t attribute_length;
  uint16_t class_index;
  uint16_t method_index;
};


struct Synthetic_attribute {
  uint16_t attribute_name_index;
  uint32_t attribute_length;
};


struct Signature_attribute {
  uint16_t attribute_name_index;
  uint32_t attribute_length;
  uint16_t signature_index;
};


struct SourceFile_attribute {
    uint16_t attribute_name_index;
    uint32_t attribute_length;
    uint16_t sourcefile_index;
};


struct SourceDebugExtension_attribute {
  uint16_t attribute_name_index;
  uint32_t attribute_length;
  uint8_t *debug_extension; /* [attribute_length] */
};


struct line_number {
  uint16_t start_pc;
  uint16_t line_number;	
};

struct LineNumberTable_attribute {
  uint16_t attribute_name_index;
  uint32_t attribute_length;
  uint16_t line_number_table_length;
  struct line_number *line_number_table; /* [line_number_table_length] */
};


struct local_variable {
  uint16_t start_pc;
  uint16_t length;
  uint16_t name_index;
  uint16_t descriptor_index;
  uint16_t index;
};

struct LocalVariableTable_attribute {
  uint16_t attribute_name_index;
  uint32_t attribute_length;
  uint16_t local_variable_table_length;
  struct local_variable *local_variable_table; /* [local_variable_table_length] */
};


struct local_variable_type {
  uint16_t start_pc;
  uint16_t length;
  uint16_t name_index;
  uint16_t signature_index;
  uint16_t index;
};

struct LocalVariableTypeTable_attribute {
  uint16_t attribute_name_index;
  uint32_t attribute_length;
  uint16_t local_variable_type_table_length;
  struct local_variable_type *local_variable_type_table; /* [local_variable_type_table_length] */
};


struct Deprecated_attribute {
  uint16_t attribute_name_index;
  uint32_t attribute_length;
};


struct element_value_pair;

struct annotation {
  uint16_t type_index;
  uint16_t num_element_value_pairs;
  struct element_value_pair *element_value_pairs; /* [num_element_value_pairs] */
};

struct element_value {
  uint8_t tag;
  union {
    uint16_t const_value_index;
    
    struct {
      uint16_t type_name_index;
      uint16_t const_name_index;
    } enum_const_value;
    
    uint16_t class_info_index;
    
    struct annotation annotation_value;
    
    struct {
      uint16_t num_values;
      struct element_value *values; /* [num_values] */
    } array_value;
  } value;
};


struct element_value_pair {
  uint16_t element_name_index;
  struct element_value value;
};


struct RuntimeVisibleAnnotations_attribute {
  uint16_t attribute_name_index;
  uint32_t attribute_length;
  uint16_t num_annotations;
  struct annotation *annotations; /* [num_annotations] */
};


struct RuntimeInvisibleAnnotations_attribute {
  uint16_t attribute_name_index;
  uint32_t attribute_length;
  uint16_t num_annotations;
  struct annotation *annotations; /* [num_annotations] */
};


struct RuntimeVisibleParameterAnnotations_attribute {
  uint16_t attribute_name_index;
  uint32_t attribute_length;
  uint8_t num_parameters;
  struct {
    uint16_t num_annotations;
    struct annotation *annotations; /* [num_annotations] */
  } *parameter_annotations; /* [num_parameters] */
};


struct RuntimeInvisibleParameterAnnotations_attribute {
  uint16_t attribute_name_index;
  uint32_t attribute_length;
  uint8_t num_parameters;
  struct {
    uint16_t num_annotations;
    struct annotation *annotations; /* [num_annotations] */
  } *parameter_annotations; /* [num_parameters] */
};


struct type_parameter_target {
    uint8_t type_parameter_index;
};

struct supertype_target {
    uint16_t supertype_index;
};

struct type_parameter_bound_target {
    uint8_t type_parameter_index;
    uint8_t bound_index;
};

struct empty_target {
  uint8_t _dummy_; // not used for anything, just have to put something here
};

struct formal_parameter_target {
    uint8_t formal_parameter_index;
};

struct throws_target {
    uint16_t throws_type_index;
};

struct localvar_target {
    uint16_t table_length;
    struct {
      uint16_t start_pc;
      uint16_t length;
      uint16_t index;
    } *table; /* [table_length] */
};

struct catch_target {
  uint16_t exception_table_index;
};

struct offset_target {
  uint16_t offset;
};

struct type_argument_target {
  uint16_t offset;
  uint8_t type_argument_index;
};

struct type_path {
  uint8_t path_length;
  struct {
    uint8_t type_path_kind;
    uint8_t type_argument_index;
  } *path; /* [path_length] */
};

struct type_annotation {
  uint8_t target_type;
  union {
    struct type_parameter_target type_parameter_target;
    struct supertype_target supertype_target;
    struct type_parameter_bound_target type_parameter_bound_target;
    struct empty_target empty_target;
    struct formal_parameter_target method_formal_parameter_target;
    struct throws_target throws_target;
    struct localvar_target localvar_target;
    struct catch_target catch_target;
    struct offset_target offset_target;
    struct type_argument_target type_argument_target;
  } target_info;
  struct type_path target_path;
  uint16_t type_index;
  uint16_t num_element_value_pairs;
  struct {
    uint16_t element_name_index;
    struct element_value value;
  } *element_value_pairs; /* [num_element_value_pairs] */
};

struct RuntimeVisibleTypeAnnotations_attribute {
  uint16_t attribute_name_index;
  uint32_t attribute_length;
  uint16_t num_annotations;
  struct type_annotation *annotations; /* [num_annotations] */
};


struct RuntimeInvisibleTypeAnnotations_attribute {
  uint16_t attribute_name_index;
  uint32_t attribute_length;
  uint16_t num_annotations;
  struct type_annotation *annotations; /* [num_annotations] */
};


struct AnnotationDefault_attribute {
    uint16_t attribute_name_index;
    uint32_t attribute_length;
    struct element_value default_value;
};


struct BootstrapMethods_attribute {
    uint16_t attribute_name_index;
    uint32_t attribute_length;
    uint16_t num_bootstrap_methods;
    struct {
      uint16_t bootstrap_method_ref;
      uint16_t num_bootstrap_arguments;
      uint16_t bootstrap_arguments; /* [num_bootstrap_arguments] */
    } *bootstrap_methods; /* [num_bootstrap_methods] */
};


struct MethodParameters_attribute {
  uint16_t attribute_name_index;
  uint32_t attribute_length;
  uint8_t parameters_count;
  struct {
    uint16_t name_index;
    uint16_t access_flags;
  } *parameters; /* [parameters_count] */
};
