#ifndef GLK_TEXTURE_RENDERER_INPUT_HPP
#define GLK_TEXTURE_RENDERER_INPUT_HPP

#include <array>
#include <unordered_map>
#include <boost/optional.hpp>

#include <Eigen/Core>

namespace glk {

struct TextureRendererInput {
  using Ptr = std::shared_ptr<TextureRendererInput>;

  EIGEN_MAKE_ALIGNED_OPERATOR_NEW
  TextureRendererInput() {}
  ~TextureRendererInput() {}

  template<typename T>
  void set(const std::string& name, const T& value);

  template<typename T>
  boost::optional<T> get(const std::string& name) const;

private:
  std::unordered_map<std::string, std::array<float, 16>> params_16f;
};

template<>
inline void TextureRendererInput::set(const std::string& name, const Eigen::Matrix4f& value) {
  std::copy(value.data(), value.data() + 16, params_16f[name].begin());
}

template<>
inline boost::optional<Eigen::Matrix4f> TextureRendererInput::get(const std::string& name) const {
  auto found = params_16f.find(name);
  if(found == params_16f.end()) {
    return boost::none;
  }

  return Eigen::Map<const Eigen::Matrix4f>(found->second.data()).eval();
}

}

#endif