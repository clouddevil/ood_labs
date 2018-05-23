#pragma once
#include "IOutlineStyle.h"
#include "IShape.h"
#include "OutlineStyle.h"


template<typename TStyle, typename V >
using DereferenceFunc = std::function< TStyle&(V const&) >;

template<typename TStyle, typename V>
class StyleIterator
	: public boost::iterator_facade<StyleIterator<T>, TStyle, std::forward_iterator_tag>
{	
public:
	using StyleIteratorT = StyleIterator<TStyle, V>;

	StyleIterator(ShapeStorage::iterator const& it, DereferenceFunc<TStyle, V> const& func)
		: m_it(it)
		, m_dereference(func)
	{
	}

	bool equal(StyleIteratorT const& other) const
	{
		return m_it == other.m_it;
	}

	void increment()
	{
		m_it++;
	}

	TStyle& dereference() const
	{
		return m_dereference(*m_it);
	}

	ShapeStorage::iterator m_it;
	DereferenceFunc<T, V> const& m_dereference;
};

template<class T>
class StyleRange
{
public:
	StyleRange(ShapeStorage& storage)
		: m_shapes(storage)
	{
	}

	StyleIterator<T, ShapeStorage::iterator> begin() const
	{
		
	}

	StyleIterator<T, ShapeStorage::iterator> end() const
	{

	}

private:
	ShapeStorage& m_shapes;
	DereferenceFunc<T> m_derefFunc;
};


class CompoundOutlineStyle
	: public IOutlineStyle
{
public:
	CompoundOutlineStyle()
	{

	}

	StyleRange<OutlineStyle> styles;

	boost::optional<RGBAColor> GetColor() const override
	{
		boost::optional<RGBAColor> color;		
		for (auto& s : styles)
		{
			auto color = s.GetColor();
			s.SetColor(0x00);
		}
		return color;
	}

	void SetColor(RGBAColor /*color*/) override
	{
		
		throw std::logic_error("The method or operation is not implemented.");
	}

	boost::optional<float> GetThickness() const override
	{
		throw std::logic_error("The method or operation is not implemented.");
	}

	void SetThickness(float /*thickness*/) override
	{
		throw std::logic_error("The method or operation is not implemented.");
	}
};
