// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: mediapipe/framework/formats/image_format.proto

#include "mediapipe/framework/formats/image_format.pb.h"

#include <algorithm>

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/wire_format_lite.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
namespace mediapipe {
class ImageFormatDefaultTypeInternal {
 public:
  ::PROTOBUF_NAMESPACE_ID::internal::ExplicitlyConstructed<ImageFormat> _instance;
} _ImageFormat_default_instance_;
}  // namespace mediapipe
static void InitDefaultsscc_info_ImageFormat_mediapipe_2fframework_2fformats_2fimage_5fformat_2eproto() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  {
    void* ptr = &::mediapipe::_ImageFormat_default_instance_;
    new (ptr) ::mediapipe::ImageFormat();
    ::PROTOBUF_NAMESPACE_ID::internal::OnShutdownDestroyMessage(ptr);
  }
  ::mediapipe::ImageFormat::InitAsDefaultInstance();
}

::PROTOBUF_NAMESPACE_ID::internal::SCCInfo<0> scc_info_ImageFormat_mediapipe_2fframework_2fformats_2fimage_5fformat_2eproto =
    {{ATOMIC_VAR_INIT(::PROTOBUF_NAMESPACE_ID::internal::SCCInfoBase::kUninitialized), 0, 0, InitDefaultsscc_info_ImageFormat_mediapipe_2fframework_2fformats_2fimage_5fformat_2eproto}, {}};

static ::PROTOBUF_NAMESPACE_ID::Metadata file_level_metadata_mediapipe_2fframework_2fformats_2fimage_5fformat_2eproto[1];
static const ::PROTOBUF_NAMESPACE_ID::EnumDescriptor* file_level_enum_descriptors_mediapipe_2fframework_2fformats_2fimage_5fformat_2eproto[1];
static constexpr ::PROTOBUF_NAMESPACE_ID::ServiceDescriptor const** file_level_service_descriptors_mediapipe_2fframework_2fformats_2fimage_5fformat_2eproto = nullptr;

const ::PROTOBUF_NAMESPACE_ID::uint32 TableStruct_mediapipe_2fframework_2fformats_2fimage_5fformat_2eproto::offsets[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  PROTOBUF_FIELD_OFFSET(::mediapipe::ImageFormat, _has_bits_),
  PROTOBUF_FIELD_OFFSET(::mediapipe::ImageFormat, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
};
static const ::PROTOBUF_NAMESPACE_ID::internal::MigrationSchema schemas[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  { 0, 5, sizeof(::mediapipe::ImageFormat)},
};

static ::PROTOBUF_NAMESPACE_ID::Message const * const file_default_instances[] = {
  reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(&::mediapipe::_ImageFormat_default_instance_),
};

const char descriptor_table_protodef_mediapipe_2fframework_2fformats_2fimage_5fformat_2eproto[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) =
  "\n.mediapipe/framework/formats/image_form"
  "at.proto\022\tmediapipe\"\271\001\n\013ImageFormat\"\251\001\n\006"
  "Format\022\013\n\007UNKNOWN\020\000\022\010\n\004SRGB\020\001\022\t\n\005SRGBA\020\002"
  "\022\t\n\005GRAY8\020\003\022\n\n\006GRAY16\020\004\022\r\n\tYCBCR420P\020\005\022\017"
  "\n\013YCBCR420P10\020\006\022\n\n\006SRGB48\020\007\022\013\n\007SRGBA64\020\010"
  "\022\013\n\007VEC32F1\020\t\022\013\n\007VEC32F2\020\014\022\010\n\004LAB8\020\n\022\t\n\005"
  "SBGRA\020\013"
  ;
static const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable*const descriptor_table_mediapipe_2fframework_2fformats_2fimage_5fformat_2eproto_deps[1] = {
};
static ::PROTOBUF_NAMESPACE_ID::internal::SCCInfoBase*const descriptor_table_mediapipe_2fframework_2fformats_2fimage_5fformat_2eproto_sccs[1] = {
  &scc_info_ImageFormat_mediapipe_2fframework_2fformats_2fimage_5fformat_2eproto.base,
};
static ::PROTOBUF_NAMESPACE_ID::internal::once_flag descriptor_table_mediapipe_2fframework_2fformats_2fimage_5fformat_2eproto_once;
static bool descriptor_table_mediapipe_2fframework_2fformats_2fimage_5fformat_2eproto_initialized = false;
const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_mediapipe_2fframework_2fformats_2fimage_5fformat_2eproto = {
  &descriptor_table_mediapipe_2fframework_2fformats_2fimage_5fformat_2eproto_initialized, descriptor_table_protodef_mediapipe_2fframework_2fformats_2fimage_5fformat_2eproto, "mediapipe/framework/formats/image_format.proto", 247,
  &descriptor_table_mediapipe_2fframework_2fformats_2fimage_5fformat_2eproto_once, descriptor_table_mediapipe_2fframework_2fformats_2fimage_5fformat_2eproto_sccs, descriptor_table_mediapipe_2fframework_2fformats_2fimage_5fformat_2eproto_deps, 1, 0,
  schemas, file_default_instances, TableStruct_mediapipe_2fframework_2fformats_2fimage_5fformat_2eproto::offsets,
  file_level_metadata_mediapipe_2fframework_2fformats_2fimage_5fformat_2eproto, 1, file_level_enum_descriptors_mediapipe_2fframework_2fformats_2fimage_5fformat_2eproto, file_level_service_descriptors_mediapipe_2fframework_2fformats_2fimage_5fformat_2eproto,
};

// Force running AddDescriptors() at dynamic initialization time.
static bool dynamic_init_dummy_mediapipe_2fframework_2fformats_2fimage_5fformat_2eproto = (  ::PROTOBUF_NAMESPACE_ID::internal::AddDescriptors(&descriptor_table_mediapipe_2fframework_2fformats_2fimage_5fformat_2eproto), true);
namespace mediapipe {
const ::PROTOBUF_NAMESPACE_ID::EnumDescriptor* ImageFormat_Format_descriptor() {
  ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(&descriptor_table_mediapipe_2fframework_2fformats_2fimage_5fformat_2eproto);
  return file_level_enum_descriptors_mediapipe_2fframework_2fformats_2fimage_5fformat_2eproto[0];
}
bool ImageFormat_Format_IsValid(int value) {
  switch (value) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
    case 11:
    case 12:
      return true;
    default:
      return false;
  }
}

#if (__cplusplus < 201703) && (!defined(_MSC_VER) || _MSC_VER >= 1900)
constexpr ImageFormat_Format ImageFormat::UNKNOWN;
constexpr ImageFormat_Format ImageFormat::SRGB;
constexpr ImageFormat_Format ImageFormat::SRGBA;
constexpr ImageFormat_Format ImageFormat::GRAY8;
constexpr ImageFormat_Format ImageFormat::GRAY16;
constexpr ImageFormat_Format ImageFormat::YCBCR420P;
constexpr ImageFormat_Format ImageFormat::YCBCR420P10;
constexpr ImageFormat_Format ImageFormat::SRGB48;
constexpr ImageFormat_Format ImageFormat::SRGBA64;
constexpr ImageFormat_Format ImageFormat::VEC32F1;
constexpr ImageFormat_Format ImageFormat::VEC32F2;
constexpr ImageFormat_Format ImageFormat::LAB8;
constexpr ImageFormat_Format ImageFormat::SBGRA;
constexpr ImageFormat_Format ImageFormat::Format_MIN;
constexpr ImageFormat_Format ImageFormat::Format_MAX;
constexpr int ImageFormat::Format_ARRAYSIZE;
#endif  // (__cplusplus < 201703) && (!defined(_MSC_VER) || _MSC_VER >= 1900)

// ===================================================================

void ImageFormat::InitAsDefaultInstance() {
}
class ImageFormat::_Internal {
 public:
  using HasBits = decltype(std::declval<ImageFormat>()._has_bits_);
};

ImageFormat::ImageFormat()
  : ::PROTOBUF_NAMESPACE_ID::Message(), _internal_metadata_(nullptr) {
  SharedCtor();
  // @@protoc_insertion_point(constructor:mediapipe.ImageFormat)
}
ImageFormat::ImageFormat(const ImageFormat& from)
  : ::PROTOBUF_NAMESPACE_ID::Message(),
      _internal_metadata_(nullptr),
      _has_bits_(from._has_bits_) {
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  // @@protoc_insertion_point(copy_constructor:mediapipe.ImageFormat)
}

void ImageFormat::SharedCtor() {
}

ImageFormat::~ImageFormat() {
  // @@protoc_insertion_point(destructor:mediapipe.ImageFormat)
  SharedDtor();
}

void ImageFormat::SharedDtor() {
}

void ImageFormat::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}
const ImageFormat& ImageFormat::default_instance() {
  ::PROTOBUF_NAMESPACE_ID::internal::InitSCC(&::scc_info_ImageFormat_mediapipe_2fframework_2fformats_2fimage_5fformat_2eproto.base);
  return *internal_default_instance();
}


void ImageFormat::Clear() {
// @@protoc_insertion_point(message_clear_start:mediapipe.ImageFormat)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  _has_bits_.Clear();
  _internal_metadata_.Clear();
}

const char* ImageFormat::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    ::PROTOBUF_NAMESPACE_ID::uint32 tag;
    ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
    CHK_(ptr);
        if ((tag & 7) == 4 || tag == 0) {
          ctx->SetLastTag(tag);
          goto success;
        }
        ptr = UnknownFieldParse(tag, &_internal_metadata_, ptr, ctx);
        CHK_(ptr != nullptr);
        continue;
  }  // while
success:
  return ptr;
failure:
  ptr = nullptr;
  goto success;
#undef CHK_
}

::PROTOBUF_NAMESPACE_ID::uint8* ImageFormat::_InternalSerialize(
    ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:mediapipe.ImageFormat)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields(), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:mediapipe.ImageFormat)
  return target;
}

size_t ImageFormat::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:mediapipe.ImageFormat)
  size_t total_size = 0;

  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    return ::PROTOBUF_NAMESPACE_ID::internal::ComputeUnknownFieldsSize(
        _internal_metadata_, total_size, &_cached_size_);
  }
  int cached_size = ::PROTOBUF_NAMESPACE_ID::internal::ToCachedSize(total_size);
  SetCachedSize(cached_size);
  return total_size;
}

void ImageFormat::MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:mediapipe.ImageFormat)
  GOOGLE_DCHECK_NE(&from, this);
  const ImageFormat* source =
      ::PROTOBUF_NAMESPACE_ID::DynamicCastToGenerated<ImageFormat>(
          &from);
  if (source == nullptr) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:mediapipe.ImageFormat)
    ::PROTOBUF_NAMESPACE_ID::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:mediapipe.ImageFormat)
    MergeFrom(*source);
  }
}

void ImageFormat::MergeFrom(const ImageFormat& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:mediapipe.ImageFormat)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

}

void ImageFormat::CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:mediapipe.ImageFormat)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void ImageFormat::CopyFrom(const ImageFormat& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:mediapipe.ImageFormat)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool ImageFormat::IsInitialized() const {
  return true;
}

void ImageFormat::InternalSwap(ImageFormat* other) {
  using std::swap;
  _internal_metadata_.Swap(&other->_internal_metadata_);
  swap(_has_bits_[0], other->_has_bits_[0]);
}

::PROTOBUF_NAMESPACE_ID::Metadata ImageFormat::GetMetadata() const {
  return GetMetadataStatic();
}


// @@protoc_insertion_point(namespace_scope)
}  // namespace mediapipe
PROTOBUF_NAMESPACE_OPEN
template<> PROTOBUF_NOINLINE ::mediapipe::ImageFormat* Arena::CreateMaybeMessage< ::mediapipe::ImageFormat >(Arena* arena) {
  return Arena::CreateInternal< ::mediapipe::ImageFormat >(arena);
}
PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>
