#pragma once
#include "util/nbt/tag.hh"

#include <memory>
#include <unordered_map>

namespace acp::nbt
{
	class TagCompound : public Tag
	{
		std::unordered_map<std::string, std::unique_ptr<Tag>> tags;

	public:
		TagCompound() = default;
		explicit TagCompound(std::unordered_map<std::string, std::unique_ptr<Tag>>&& tags);

		void read(ByteBuf& buf) override;
		void write(ByteBuf& buf) override;

		std::unordered_map<std::string, std::unique_ptr<Tag>>& get();
		const std::unordered_map<std::string, std::unique_ptr<Tag>>& get() const;

		bool contains(const std::string& name) const;

		std::unique_ptr<Tag>& get(const std::string& name);
		const std::unique_ptr<Tag>& get(const std::string& name) const;

		/// simple tag getter helper
		/// @tparam T cast to type
		/// @tparam P nbt tag type
		/// @param name mapped name
		/// @return mapped value
		template<class T, class P>
		T get(const std::string& name)
		{
			std::unique_ptr<Tag>& tag = tags[name];
			P* ptr = dynamic_cast<P*>(tag.get());
			return ptr->get();
		}

		void set(const std::string& name, std::unique_ptr<Tag>&& tag);

		template<class T, class ...Args>
		void set(const std::string& name, Args&& ...args)
		{
			set(name, std::make_unique<T>(std::forward<Args...>(args...)));
		}

		TagType getType() const override;

		std::string toString() const override;
	};
}
