#pragma once
namespace OR2L
{
	class IORParserComponent
	{
	public:
		IORParserComponent() = default;

		IORParserComponent(const IORParserComponent &) = default;
		IORParserComponent(IORParserComponent &&) = default;
		virtual IORParserComponent &operator=(const IORParserComponent &) = default;
		virtual IORParserComponent &operator=(IORParserComponent &&) = default;
		virtual ~IORParserComponent() = default;

	private:
	};
} // namespace OR2L
