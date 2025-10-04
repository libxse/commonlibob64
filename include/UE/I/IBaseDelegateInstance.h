#pragma once

namespace UE
{
	template <class F, class P>
	class IBaseDelegateInstance;

	template <class>
	class TDelegateBase;

	struct FNotThreadSafeDelegateMode;
	struct FNotThreadSafeNotCheckedDelegateMode;
	struct FThreadSafeDelegateMode;

	template <class R, class... A, class P>
	class IBaseDelegateInstance<R(A...), P> :
		public P::FDelegateInstanceExtras
	{
	public:
		virtual void CreateCopy(TDelegateBase<FThreadSafeDelegateMode>& a_base) const = 0;
		virtual void CreateCopy(TDelegateBase<FNotThreadSafeDelegateMode>& a_base) const = 0;
		virtual void CreateCopy(TDelegateBase<FNotThreadSafeNotCheckedDelegateMode>& a_base) const = 0;
		virtual R    Execute(A...) const = 0;
		virtual bool ExecuteIfSafe(A...) const = 0;
	};
}
