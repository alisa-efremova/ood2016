#pragma once

template <typename T>
class IObserver
{
public:
	virtual void Update(T const& subject) = 0;
	virtual ~IObserver() = default;
};