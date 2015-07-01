#ifndef __RQ_FAST_H__
#define __RQ_FAST_H__

#include <mfast.h>
#include <boost/array.hpp>
namespace rq_fast
{

	class cffexl2_cref
		: public mfast::aggregate_cref
	{
		typedef mfast::aggregate_cref base_type;
	public:
		typedef mfast::template_instruction_ex<cffexl2_cref> instruction_type;
		typedef const instruction_type *instruction_cptr;
		cffexl2_cref();
		template <typename T>
		cffexl2_cref(
			typename std::enable_if<std::is_same<typename T::cref_type, cffexl2_cref>::value, const mfast::value_storage *>::type
			storage,
			const T *instruction);

		cffexl2_cref(const mfast::message_cref &other);

		explicit cffexl2_cref(const mfast::field_cref &other);

		operator mfast::message_cref();
		template <typename Visitor>
		void accept(Visitor &v);

		mfast::int32_cref get_protocol_ver() const;
		mfast::int32_cref try_get_protocol_ver() const;
		mfast::uint64_cref get_timestamp() const;
		mfast::uint64_cref try_get_timestamp() const;
		mfast::ascii_string_cref get_trading_day() const;
		mfast::ascii_string_cref try_get_trading_day() const;
		mfast::ascii_string_cref get_settlement_GID() const;
		mfast::ascii_string_cref try_get_settlement_GID() const;
		mfast::int32_cref get_settlement_ID() const;
		mfast::int32_cref try_get_settlement_ID() const;
		mfast::decimal_cref get_last_price() const;
		mfast::decimal_cref try_get_last_price() const;
		mfast::decimal_cref get_pre_settlement_price() const;
		mfast::decimal_cref try_get_pre_settlement_price() const;
		mfast::decimal_cref get_pre_close_price() const;
		mfast::decimal_cref try_get_pre_close_price() const;
		mfast::decimal_cref get_pre_open_interest() const;
		mfast::decimal_cref try_get_pre_open_interest() const;
		mfast::decimal_cref get_open_price() const;
		mfast::decimal_cref try_get_open_price() const;
		mfast::decimal_cref get_highest_price() const;
		mfast::decimal_cref try_get_highest_price() const;
		mfast::decimal_cref get_lowest_price() const;
		mfast::decimal_cref try_get_lowest_price() const;
		mfast::int32_cref get_total_volume() const;
		mfast::int32_cref try_get_total_volume() const;
		mfast::decimal_cref get_total_turnover() const;
		mfast::decimal_cref try_get_total_turnover() const;
		mfast::decimal_cref get_open_interest() const;
		mfast::decimal_cref try_get_open_interest() const;
		mfast::decimal_cref get_close_price() const;
		mfast::decimal_cref try_get_close_price() const;
		mfast::decimal_cref get_settlement_price() const;
		mfast::decimal_cref try_get_settlement_price() const;
		mfast::decimal_cref get_upper_limit_price() const;
		mfast::decimal_cref try_get_upper_limit_price() const;
		mfast::decimal_cref get_lower_limit_price() const;
		mfast::decimal_cref try_get_lower_limit_price() const;
		mfast::decimal_cref get_pre_delta() const;
		mfast::decimal_cref try_get_pre_delta() const;
		mfast::decimal_cref get_cur_delta() const;
		mfast::decimal_cref try_get_cur_delta() const;
		mfast::ascii_string_cref get_update_time() const;
		mfast::ascii_string_cref try_get_update_time() const;
		mfast::int32_cref get_update_ms() const;
		mfast::int32_cref try_get_update_ms() const;
		mfast::ascii_string_cref get_instrument_id() const;
		mfast::ascii_string_cref try_get_instrument_id() const;

		class bid_ask_pvs_element_cref
			: public mfast::sequence_element_cref
		{
			typedef mfast::sequence_element_cref base_type;
		public:
			typedef mfast::sequence_instruction_ex<bid_ask_pvs_element_cref>
			instruction_type;
			typedef const instruction_type *instruction_cptr;
			bid_ask_pvs_element_cref(
				const mfast::value_storage *storage,
				instruction_cptr            instruction);

			template <typename Visitor>
			void accept(Visitor &v);

			mfast::decimal_cref get_level_price() const;
			mfast::decimal_cref try_get_level_price() const;
			mfast::int32_cref get_level_vol() const;
			mfast::int32_cref try_get_level_vol() const;
		};

		typedef mfast::make_sequence_cref<bid_ask_pvs_element_cref> bid_ask_pvs_cref;
		bid_ask_pvs_cref get_bid_ask_pvs() const;
		bid_ask_pvs_cref try_get_bid_ask_pvs() const;

	};


	typedef mfast::make_aggregate_mref<cffexl2_cref> cffexl2_mref_base;
	class cffexl2_mref
		: public cffexl2_mref_base
	{
		typedef cffexl2_mref_base base_type;
	public:
		typedef mfast::template_instruction_ex<cffexl2_cref> instruction_type;
		typedef const instruction_type *instruction_cptr;
		cffexl2_mref();
		template <typename T>
		cffexl2_mref(
			mfast::allocator       *alloc,
			typename std::enable_if<std::is_same<typename T::cref_type, cffexl2_cref>::value, mfast::value_storage *>::type
			storage,
			const T *instruction);

		cffexl2_mref(const mfast::message_mref &other);

		operator mfast::message_mref();
		explicit cffexl2_mref(const mfast::field_mref_base &other);

		template <typename Visitor>
		void accept(Visitor &v);

		mfast::int32_mref set_protocol_ver() const;
		mfast::uint64_mref set_timestamp() const;
		mfast::ascii_string_mref set_trading_day() const;
		mfast::ascii_string_mref set_settlement_GID() const;
		mfast::int32_mref set_settlement_ID() const;
		mfast::decimal_mref set_last_price() const;
		mfast::decimal_mref set_pre_settlement_price() const;
		mfast::decimal_mref set_pre_close_price() const;
		mfast::decimal_mref set_pre_open_interest() const;
		mfast::decimal_mref set_open_price() const;
		mfast::decimal_mref set_highest_price() const;
		mfast::decimal_mref set_lowest_price() const;
		mfast::int32_mref set_total_volume() const;
		mfast::decimal_mref set_total_turnover() const;
		mfast::decimal_mref set_open_interest() const;
		mfast::decimal_mref set_close_price() const;
		mfast::decimal_mref set_settlement_price() const;
		mfast::decimal_mref set_upper_limit_price() const;
		mfast::decimal_mref set_lower_limit_price() const;
		mfast::decimal_mref set_pre_delta() const;
		mfast::decimal_mref set_cur_delta() const;
		mfast::ascii_string_mref set_update_time() const;
		mfast::int32_mref set_update_ms() const;
		mfast::ascii_string_mref set_instrument_id() const;

		class bid_ask_pvs_element_mref
			: public mfast::make_aggregate_mref<cffexl2_cref::bid_ask_pvs_element_cref>
		{
			typedef mfast::make_aggregate_mref<cffexl2_cref::bid_ask_pvs_element_cref>
			base_type;
		public:
			bid_ask_pvs_element_mref(
				mfast::allocator     *alloc,
				mfast::value_storage *storage,
				instruction_cptr      instruction);

			template <typename Visitor>
			void accept(Visitor &v);

			mfast::decimal_mref set_level_price() const;
			mfast::int32_mref set_level_vol() const;
		};

		typedef mfast::make_sequence_mref<bid_ask_pvs_element_mref> bid_ask_pvs_mref;
		bid_ask_pvs_mref set_bid_ask_pvs() const;
	};

	class cffexl2
		: private mfast::value_storage_array<25>
		, public mfast::message_type
	{
		typedef mfast::message_type base_type;
	public:
		enum {
			the_id = 11
		};
		typedef mfast::template_instruction_ex<cffexl2_cref> instruction_type;

		typedef mfast::make_message_cref<cffexl2_cref, instruction_type> cref_type;
		typedef mfast::make_message_mref<cffexl2_mref, instruction_type> mref_type;
		cffexl2(
			mfast::allocator *alloc=mfast::malloc_allocator::instance());
		cffexl2(
			const cffexl2_cref &other,
			mfast::allocator *alloc=mfast::malloc_allocator::instance());
		cref_type ref() const;
		cref_type cref() const;
		mref_type ref();
		mref_type mref();
		static const instruction_type *instruction();
	private:
		cffexl2(const cffexl2 &);
		cffexl2 &operator = (const cffexl2 &);
	};


	class dcel2_MDBestAndDeep_cref
		: public mfast::aggregate_cref
	{
		typedef mfast::aggregate_cref base_type;
	public:
		typedef mfast::template_instruction_ex<dcel2_MDBestAndDeep_cref>
		instruction_type;
		typedef const instruction_type *instruction_cptr;
		dcel2_MDBestAndDeep_cref();
		template <typename T>
		dcel2_MDBestAndDeep_cref(
			typename std::enable_if<std::is_same<typename T::cref_type, dcel2_MDBestAndDeep_cref>::value, const mfast::value_storage *>::type
			storage,
			const T *instruction);

		dcel2_MDBestAndDeep_cref(const mfast::message_cref &other);

		explicit dcel2_MDBestAndDeep_cref(const mfast::field_cref &other);

		operator mfast::message_cref();
		template <typename Visitor>
		void accept(Visitor &v);

		mfast::int32_cref get_protocol_ver() const;
		mfast::int32_cref try_get_protocol_ver() const;
		mfast::int32_cref get_type() const;
		mfast::int32_cref try_get_type() const;
		mfast::uint32_cref get_length() const;
		mfast::uint32_cref try_get_length() const;
		mfast::uint32_cref get_version() const;
		mfast::uint32_cref try_get_version() const;
		mfast::uint32_cref get_time() const;
		mfast::uint32_cref try_get_time() const;
		mfast::ascii_string_cref get_exchange() const;
		mfast::ascii_string_cref try_get_exchange() const;
		mfast::ascii_string_cref get_contract() const;
		mfast::ascii_string_cref try_get_contract() const;
		mfast::int32_cref get_suspension_sign() const;
		mfast::int32_cref try_get_suspension_sign() const;
		mfast::decimal_cref get_last_clear_price() const;
		mfast::decimal_cref try_get_last_clear_price() const;
		mfast::decimal_cref get_clear_price() const;
		mfast::decimal_cref try_get_clear_price() const;
		mfast::decimal_cref get_avg_price() const;
		mfast::decimal_cref try_get_avg_price() const;
		mfast::decimal_cref get_last_close_price() const;
		mfast::decimal_cref try_get_last_close_price() const;
		mfast::decimal_cref get_close_price() const;
		mfast::decimal_cref try_get_close_price() const;
		mfast::decimal_cref get_open_price() const;
		mfast::decimal_cref try_get_open_price() const;
		mfast::uint32_cref get_last_open_interest() const;
		mfast::uint32_cref try_get_last_open_interest() const;
		mfast::uint32_cref get_open_interest() const;
		mfast::uint32_cref try_get_open_interest() const;
		mfast::decimal_cref get_last_price() const;
		mfast::decimal_cref try_get_last_price() const;
		mfast::uint32_cref get_match_tot_qty() const;
		mfast::uint32_cref try_get_match_tot_qty() const;
		mfast::decimal_cref get_turn_over() const;
		mfast::decimal_cref try_get_turn_over() const;
		mfast::decimal_cref get_rise_limit_price() const;
		mfast::decimal_cref try_get_rise_limit_price() const;
		mfast::decimal_cref get_fall_limit_price() const;
		mfast::decimal_cref try_get_fall_limit_price() const;
		mfast::decimal_cref get_high_price() const;
		mfast::decimal_cref try_get_high_price() const;
		mfast::decimal_cref get_low_price() const;
		mfast::decimal_cref try_get_low_price() const;
		mfast::decimal_cref get_pre_delta() const;
		mfast::decimal_cref try_get_pre_delta() const;
		mfast::decimal_cref get_cur_delta() const;
		mfast::decimal_cref try_get_cur_delta() const;

		class bid_ask_pvs_element_cref
			: public mfast::sequence_element_cref
		{
			typedef mfast::sequence_element_cref base_type;
		public:
			typedef mfast::sequence_instruction_ex<bid_ask_pvs_element_cref>
			instruction_type;
			typedef const instruction_type *instruction_cptr;
			bid_ask_pvs_element_cref(
				const mfast::value_storage *storage,
				instruction_cptr            instruction);

			template <typename Visitor>
			void accept(Visitor &v);

			mfast::decimal_cref get_level_price() const;
			mfast::decimal_cref try_get_level_price() const;
			mfast::int32_cref get_level_vol() const;
			mfast::int32_cref try_get_level_vol() const;
			mfast::int32_cref get_level_imply_vol() const;
			mfast::int32_cref try_get_level_imply_vol() const;
		};

		typedef mfast::make_sequence_cref<bid_ask_pvs_element_cref> bid_ask_pvs_cref;
		bid_ask_pvs_cref get_bid_ask_pvs() const;
		bid_ask_pvs_cref try_get_bid_ask_pvs() const;
		mfast::ascii_string_cref get_gen_time() const;
		mfast::ascii_string_cref try_get_gen_time() const;
		mfast::uint32_cref get_last_match_vol() const;
		mfast::uint32_cref try_get_last_match_vol() const;
		mfast::int32_cref get_interest_change() const;
		mfast::int32_cref try_get_interest_change() const;
		mfast::decimal_cref get_life_low() const;
		mfast::decimal_cref try_get_life_low() const;
		mfast::decimal_cref get_life_high() const;
		mfast::decimal_cref try_get_life_high() const;
		mfast::decimal_cref get_delta() const;
		mfast::decimal_cref try_get_delta() const;
		mfast::decimal_cref get_gamma() const;
		mfast::decimal_cref try_get_gamma() const;
		mfast::decimal_cref get_rho() const;
		mfast::decimal_cref try_get_rho() const;
		mfast::decimal_cref get_theta() const;
		mfast::decimal_cref try_get_theta() const;
		mfast::decimal_cref get_vega() const;
		mfast::decimal_cref try_get_vega() const;
		mfast::ascii_string_cref get_trade_date() const;
		mfast::ascii_string_cref try_get_trade_date() const;
		mfast::ascii_string_cref get_local_date() const;
		mfast::ascii_string_cref try_get_local_date() const;

	};


	typedef mfast::make_aggregate_mref<dcel2_MDBestAndDeep_cref>
	dcel2_MDBestAndDeep_mref_base;
	class dcel2_MDBestAndDeep_mref
		: public dcel2_MDBestAndDeep_mref_base
	{
		typedef dcel2_MDBestAndDeep_mref_base base_type;
	public:
		typedef mfast::template_instruction_ex<dcel2_MDBestAndDeep_cref>
		instruction_type;
		typedef const instruction_type *instruction_cptr;
		dcel2_MDBestAndDeep_mref();
		template <typename T>
		dcel2_MDBestAndDeep_mref(
			mfast::allocator       *alloc,
			typename std::enable_if<std::is_same<typename T::cref_type, dcel2_MDBestAndDeep_cref>::value, mfast::value_storage *>::type
			storage,
			const T *instruction);

		dcel2_MDBestAndDeep_mref(const mfast::message_mref &other);

		operator mfast::message_mref();
		explicit dcel2_MDBestAndDeep_mref(const mfast::field_mref_base &other);

		template <typename Visitor>
		void accept(Visitor &v);

		mfast::int32_mref set_protocol_ver() const;
		mfast::int32_mref set_type() const;
		mfast::uint32_mref set_length() const;
		mfast::uint32_mref set_version() const;
		mfast::uint32_mref set_time() const;
		mfast::ascii_string_mref set_exchange() const;
		mfast::ascii_string_mref set_contract() const;
		mfast::int32_mref set_suspension_sign() const;
		mfast::decimal_mref set_last_clear_price() const;
		mfast::decimal_mref set_clear_price() const;
		mfast::decimal_mref set_avg_price() const;
		mfast::decimal_mref set_last_close_price() const;
		mfast::decimal_mref set_close_price() const;
		mfast::decimal_mref set_open_price() const;
		mfast::uint32_mref set_last_open_interest() const;
		mfast::uint32_mref set_open_interest() const;
		mfast::decimal_mref set_last_price() const;
		mfast::uint32_mref set_match_tot_qty() const;
		mfast::decimal_mref set_turn_over() const;
		mfast::decimal_mref set_rise_limit_price() const;
		mfast::decimal_mref set_fall_limit_price() const;
		mfast::decimal_mref set_high_price() const;
		mfast::decimal_mref set_low_price() const;
		mfast::decimal_mref set_pre_delta() const;
		mfast::decimal_mref set_cur_delta() const;

		class bid_ask_pvs_element_mref
			: public mfast::make_aggregate_mref<dcel2_MDBestAndDeep_cref::bid_ask_pvs_element_cref>
		{
			typedef mfast::make_aggregate_mref<dcel2_MDBestAndDeep_cref::bid_ask_pvs_element_cref>
			base_type;
		public:
			bid_ask_pvs_element_mref(
				mfast::allocator     *alloc,
				mfast::value_storage *storage,
				instruction_cptr      instruction);

			template <typename Visitor>
			void accept(Visitor &v);

			mfast::decimal_mref set_level_price() const;
			mfast::int32_mref set_level_vol() const;
			mfast::int32_mref set_level_imply_vol() const;
		};

		typedef mfast::make_sequence_mref<bid_ask_pvs_element_mref> bid_ask_pvs_mref;
		bid_ask_pvs_mref set_bid_ask_pvs() const;
		mfast::ascii_string_mref set_gen_time() const;
		mfast::uint32_mref set_last_match_vol() const;
		mfast::int32_mref set_interest_change() const;
		mfast::decimal_mref set_life_low() const;
		mfast::decimal_mref set_life_high() const;
		mfast::decimal_mref set_delta() const;
		mfast::decimal_mref set_gamma() const;
		mfast::decimal_mref set_rho() const;
		mfast::decimal_mref set_theta() const;
		mfast::decimal_mref set_vega() const;
		mfast::ascii_string_mref set_trade_date() const;
		mfast::ascii_string_mref set_local_date() const;
	};

	class dcel2_MDBestAndDeep
		: private mfast::value_storage_array<38>
		, public mfast::message_type
	{
		typedef mfast::message_type base_type;
	public:
		enum {
			the_id = 2
		};
		typedef mfast::template_instruction_ex<dcel2_MDBestAndDeep_cref>
		instruction_type;

		typedef mfast::make_message_cref<dcel2_MDBestAndDeep_cref, instruction_type>
		cref_type;
		typedef mfast::make_message_mref<dcel2_MDBestAndDeep_mref, instruction_type>
		mref_type;
		dcel2_MDBestAndDeep(
			mfast::allocator *alloc=mfast::malloc_allocator::instance());
		dcel2_MDBestAndDeep(
			const dcel2_MDBestAndDeep_cref &other,
			mfast::allocator *alloc=mfast::malloc_allocator::instance());
		cref_type ref() const;
		cref_type cref() const;
		mref_type ref();
		mref_type mref();
		static const instruction_type *instruction();
	private:
		dcel2_MDBestAndDeep(const dcel2_MDBestAndDeep &);
		dcel2_MDBestAndDeep &operator = (const dcel2_MDBestAndDeep &);
	};


	class dcel2_MArbi_cref
		: public mfast::aggregate_cref
	{
		typedef mfast::aggregate_cref base_type;
	public:
		typedef mfast::template_instruction_ex<dcel2_MArbi_cref> instruction_type;
		typedef const instruction_type *instruction_cptr;
		dcel2_MArbi_cref();
		template <typename T>
		dcel2_MArbi_cref(
			typename std::enable_if<std::is_same<typename T::cref_type, dcel2_MArbi_cref>::value, const mfast::value_storage *>::type
			storage,
			const T *instruction);

		dcel2_MArbi_cref(const mfast::message_cref &other);

		explicit dcel2_MArbi_cref(const mfast::field_cref &other);

		operator mfast::message_cref();
		template <typename Visitor>
		void accept(Visitor &v);

		mfast::int32_cref get_protocol_ver() const;
		mfast::int32_cref try_get_protocol_ver() const;
		mfast::int32_cref get_type() const;
		mfast::int32_cref try_get_type() const;
		mfast::uint32_cref get_length() const;
		mfast::uint32_cref try_get_length() const;
		mfast::uint32_cref get_version() const;
		mfast::uint32_cref try_get_version() const;
		mfast::uint32_cref get_time() const;
		mfast::uint32_cref try_get_time() const;
		mfast::ascii_string_cref get_exchange() const;
		mfast::ascii_string_cref try_get_exchange() const;
		mfast::ascii_string_cref get_contract() const;
		mfast::ascii_string_cref try_get_contract() const;
		mfast::int32_cref get_suspension_sign() const;
		mfast::int32_cref try_get_suspension_sign() const;
		mfast::decimal_cref get_last_clear_price() const;
		mfast::decimal_cref try_get_last_clear_price() const;
		mfast::decimal_cref get_clear_price() const;
		mfast::decimal_cref try_get_clear_price() const;
		mfast::decimal_cref get_avg_price() const;
		mfast::decimal_cref try_get_avg_price() const;
		mfast::decimal_cref get_last_close_price() const;
		mfast::decimal_cref try_get_last_close_price() const;
		mfast::decimal_cref get_close_price() const;
		mfast::decimal_cref try_get_close_price() const;
		mfast::decimal_cref get_open_price() const;
		mfast::decimal_cref try_get_open_price() const;
		mfast::uint32_cref get_last_open_interest() const;
		mfast::uint32_cref try_get_last_open_interest() const;
		mfast::uint32_cref get_open_interest() const;
		mfast::uint32_cref try_get_open_interest() const;
		mfast::decimal_cref get_last_price() const;
		mfast::decimal_cref try_get_last_price() const;
		mfast::uint32_cref get_match_tot_qty() const;
		mfast::uint32_cref try_get_match_tot_qty() const;
		mfast::decimal_cref get_turn_over() const;
		mfast::decimal_cref try_get_turn_over() const;
		mfast::decimal_cref get_rise_limit_price() const;
		mfast::decimal_cref try_get_rise_limit_price() const;
		mfast::decimal_cref get_fall_limit_price() const;
		mfast::decimal_cref try_get_fall_limit_price() const;
		mfast::decimal_cref get_high_price() const;
		mfast::decimal_cref try_get_high_price() const;
		mfast::decimal_cref get_low_price() const;
		mfast::decimal_cref try_get_low_price() const;
		mfast::decimal_cref get_pre_delta() const;
		mfast::decimal_cref try_get_pre_delta() const;
		mfast::decimal_cref get_cur_delta() const;
		mfast::decimal_cref try_get_cur_delta() const;

		class bid_ask_pvs_element_cref
			: public mfast::sequence_element_cref
		{
			typedef mfast::sequence_element_cref base_type;
		public:
			typedef mfast::sequence_instruction_ex<bid_ask_pvs_element_cref>
			instruction_type;
			typedef const instruction_type *instruction_cptr;
			bid_ask_pvs_element_cref(
				const mfast::value_storage *storage,
				instruction_cptr            instruction);

			template <typename Visitor>
			void accept(Visitor &v);

			mfast::decimal_cref get_level_price() const;
			mfast::decimal_cref try_get_level_price() const;
			mfast::int32_cref get_level_vol() const;
			mfast::int32_cref try_get_level_vol() const;
			mfast::int32_cref get_level_imply_vol() const;
			mfast::int32_cref try_get_level_imply_vol() const;
		};

		typedef mfast::make_sequence_cref<bid_ask_pvs_element_cref> bid_ask_pvs_cref;
		bid_ask_pvs_cref get_bid_ask_pvs() const;
		bid_ask_pvs_cref try_get_bid_ask_pvs() const;
		mfast::ascii_string_cref get_gen_time() const;
		mfast::ascii_string_cref try_get_gen_time() const;
		mfast::uint32_cref get_last_match_vol() const;
		mfast::uint32_cref try_get_last_match_vol() const;
		mfast::int32_cref get_interest_change() const;
		mfast::int32_cref try_get_interest_change() const;
		mfast::decimal_cref get_life_low() const;
		mfast::decimal_cref try_get_life_low() const;
		mfast::decimal_cref get_life_high() const;
		mfast::decimal_cref try_get_life_high() const;
		mfast::decimal_cref get_delta() const;
		mfast::decimal_cref try_get_delta() const;
		mfast::decimal_cref get_gamma() const;
		mfast::decimal_cref try_get_gamma() const;
		mfast::decimal_cref get_rho() const;
		mfast::decimal_cref try_get_rho() const;
		mfast::decimal_cref get_theta() const;
		mfast::decimal_cref try_get_theta() const;
		mfast::decimal_cref get_vega() const;
		mfast::decimal_cref try_get_vega() const;
		mfast::ascii_string_cref get_trade_date() const;
		mfast::ascii_string_cref try_get_trade_date() const;
		mfast::ascii_string_cref get_local_date() const;
		mfast::ascii_string_cref try_get_local_date() const;

	};


	typedef mfast::make_aggregate_mref<dcel2_MArbi_cref> dcel2_MArbi_mref_base;
	class dcel2_MArbi_mref
		: public dcel2_MArbi_mref_base
	{
		typedef dcel2_MArbi_mref_base base_type;
	public:
		typedef mfast::template_instruction_ex<dcel2_MArbi_cref> instruction_type;
		typedef const instruction_type *instruction_cptr;
		dcel2_MArbi_mref();
		template <typename T>
		dcel2_MArbi_mref(
			mfast::allocator       *alloc,
			typename std::enable_if<std::is_same<typename T::cref_type, dcel2_MArbi_cref>::value, mfast::value_storage *>::type
			storage,
			const T *instruction);

		dcel2_MArbi_mref(const mfast::message_mref &other);

		operator mfast::message_mref();
		explicit dcel2_MArbi_mref(const mfast::field_mref_base &other);

		template <typename Visitor>
		void accept(Visitor &v);

		mfast::int32_mref set_protocol_ver() const;
		mfast::int32_mref set_type() const;
		mfast::uint32_mref set_length() const;
		mfast::uint32_mref set_version() const;
		mfast::uint32_mref set_time() const;
		mfast::ascii_string_mref set_exchange() const;
		mfast::ascii_string_mref set_contract() const;
		mfast::int32_mref set_suspension_sign() const;
		mfast::decimal_mref set_last_clear_price() const;
		mfast::decimal_mref set_clear_price() const;
		mfast::decimal_mref set_avg_price() const;
		mfast::decimal_mref set_last_close_price() const;
		mfast::decimal_mref set_close_price() const;
		mfast::decimal_mref set_open_price() const;
		mfast::uint32_mref set_last_open_interest() const;
		mfast::uint32_mref set_open_interest() const;
		mfast::decimal_mref set_last_price() const;
		mfast::uint32_mref set_match_tot_qty() const;
		mfast::decimal_mref set_turn_over() const;
		mfast::decimal_mref set_rise_limit_price() const;
		mfast::decimal_mref set_fall_limit_price() const;
		mfast::decimal_mref set_high_price() const;
		mfast::decimal_mref set_low_price() const;
		mfast::decimal_mref set_pre_delta() const;
		mfast::decimal_mref set_cur_delta() const;

		class bid_ask_pvs_element_mref
			: public mfast::make_aggregate_mref<dcel2_MArbi_cref::bid_ask_pvs_element_cref>
		{
			typedef mfast::make_aggregate_mref<dcel2_MArbi_cref::bid_ask_pvs_element_cref>
			base_type;
		public:
			bid_ask_pvs_element_mref(
				mfast::allocator     *alloc,
				mfast::value_storage *storage,
				instruction_cptr      instruction);

			template <typename Visitor>
			void accept(Visitor &v);

			mfast::decimal_mref set_level_price() const;
			mfast::int32_mref set_level_vol() const;
			mfast::int32_mref set_level_imply_vol() const;
		};

		typedef mfast::make_sequence_mref<bid_ask_pvs_element_mref> bid_ask_pvs_mref;
		bid_ask_pvs_mref set_bid_ask_pvs() const;
		mfast::ascii_string_mref set_gen_time() const;
		mfast::uint32_mref set_last_match_vol() const;
		mfast::int32_mref set_interest_change() const;
		mfast::decimal_mref set_life_low() const;
		mfast::decimal_mref set_life_high() const;
		mfast::decimal_mref set_delta() const;
		mfast::decimal_mref set_gamma() const;
		mfast::decimal_mref set_rho() const;
		mfast::decimal_mref set_theta() const;
		mfast::decimal_mref set_vega() const;
		mfast::ascii_string_mref set_trade_date() const;
		mfast::ascii_string_mref set_local_date() const;
	};

	class dcel2_MArbi
		: private mfast::value_storage_array<38>
		, public mfast::message_type
	{
		typedef mfast::message_type base_type;
	public:
		enum {
			the_id = 3
		};
		typedef mfast::template_instruction_ex<dcel2_MArbi_cref> instruction_type;

		typedef mfast::make_message_cref<dcel2_MArbi_cref, instruction_type> cref_type;
		typedef mfast::make_message_mref<dcel2_MArbi_mref, instruction_type> mref_type;
		dcel2_MArbi(
			mfast::allocator *alloc=mfast::malloc_allocator::instance());
		dcel2_MArbi(
			const dcel2_MArbi_cref &other,
			mfast::allocator *alloc=mfast::malloc_allocator::instance());
		cref_type ref() const;
		cref_type cref() const;
		mref_type ref();
		mref_type mref();
		static const instruction_type *instruction();
	private:
		dcel2_MArbi(const dcel2_MArbi &);
		dcel2_MArbi &operator = (const dcel2_MArbi &);
	};


	class dcel2_MD10Entrust_cref
		: public mfast::aggregate_cref
	{
		typedef mfast::aggregate_cref base_type;
	public:
		typedef mfast::template_instruction_ex<dcel2_MD10Entrust_cref> instruction_type;
		typedef const instruction_type *instruction_cptr;
		dcel2_MD10Entrust_cref();
		template <typename T>
		dcel2_MD10Entrust_cref(
			typename std::enable_if<std::is_same<typename T::cref_type, dcel2_MD10Entrust_cref>::value, const mfast::value_storage *>::type
			storage,
			const T *instruction);

		dcel2_MD10Entrust_cref(const mfast::message_cref &other);

		explicit dcel2_MD10Entrust_cref(const mfast::field_cref &other);

		operator mfast::message_cref();
		template <typename Visitor>
		void accept(Visitor &v);

		mfast::int32_cref get_version() const;
		mfast::int32_cref try_get_version() const;
		mfast::int32_cref get_type() const;
		mfast::int32_cref try_get_type() const;
		mfast::uint32_cref get_length() const;
		mfast::uint32_cref try_get_length() const;
		mfast::ascii_string_cref get_contract() const;
		mfast::ascii_string_cref try_get_contract() const;
		mfast::decimal_cref get_bestbid_order_price() const;
		mfast::decimal_cref try_get_bestbid_order_price() const;

		class best_bid_vols_element_cref
			: public mfast::sequence_element_cref
		{
			typedef mfast::sequence_element_cref base_type;
		public:
			typedef mfast::sequence_instruction_ex<best_bid_vols_element_cref>
			instruction_type;
			typedef const instruction_type *instruction_cptr;
			best_bid_vols_element_cref(
				const mfast::value_storage *storage,
				instruction_cptr            instruction);

			template <typename Visitor>
			void accept(Visitor &v);

			mfast::decimal_cref get_bid_price() const;
			mfast::decimal_cref try_get_bid_price() const;
		};

		typedef mfast::make_sequence_cref<best_bid_vols_element_cref>
		best_bid_vols_cref;
		best_bid_vols_cref get_best_bid_vols() const;
		best_bid_vols_cref try_get_best_bid_vols() const;
		mfast::decimal_cref get_bestask_order_price() const;
		mfast::decimal_cref try_get_bestask_order_price() const;

		class best_ask_vols_element_cref
			: public mfast::sequence_element_cref
		{
			typedef mfast::sequence_element_cref base_type;
		public:
			typedef mfast::sequence_instruction_ex<best_ask_vols_element_cref>
			instruction_type;
			typedef const instruction_type *instruction_cptr;
			best_ask_vols_element_cref(
				const mfast::value_storage *storage,
				instruction_cptr            instruction);

			template <typename Visitor>
			void accept(Visitor &v);

			mfast::decimal_cref get_ask_price() const;
			mfast::decimal_cref try_get_ask_price() const;
		};

		typedef mfast::make_sequence_cref<best_ask_vols_element_cref>
		best_ask_vols_cref;
		best_ask_vols_cref get_best_ask_vols() const;
		best_ask_vols_cref try_get_best_ask_vols() const;
		mfast::ascii_string_cref get_gentime() const;
		mfast::ascii_string_cref try_get_gentime() const;

	};


	typedef mfast::make_aggregate_mref<dcel2_MD10Entrust_cref>
	dcel2_MD10Entrust_mref_base;
	class dcel2_MD10Entrust_mref
		: public dcel2_MD10Entrust_mref_base
	{
		typedef dcel2_MD10Entrust_mref_base base_type;
	public:
		typedef mfast::template_instruction_ex<dcel2_MD10Entrust_cref> instruction_type;
		typedef const instruction_type *instruction_cptr;
		dcel2_MD10Entrust_mref();
		template <typename T>
		dcel2_MD10Entrust_mref(
			mfast::allocator       *alloc,
			typename std::enable_if<std::is_same<typename T::cref_type, dcel2_MD10Entrust_cref>::value, mfast::value_storage *>::type
			storage,
			const T *instruction);

		dcel2_MD10Entrust_mref(const mfast::message_mref &other);

		operator mfast::message_mref();
		explicit dcel2_MD10Entrust_mref(const mfast::field_mref_base &other);

		template <typename Visitor>
		void accept(Visitor &v);

		mfast::int32_mref set_version() const;
		mfast::int32_mref set_type() const;
		mfast::uint32_mref set_length() const;
		mfast::ascii_string_mref set_contract() const;
		mfast::decimal_mref set_bestbid_order_price() const;

		class best_bid_vols_element_mref
			: public mfast::make_aggregate_mref<dcel2_MD10Entrust_cref::best_bid_vols_element_cref>
		{
			typedef mfast::make_aggregate_mref<dcel2_MD10Entrust_cref::best_bid_vols_element_cref>
			base_type;
		public:
			best_bid_vols_element_mref(
				mfast::allocator     *alloc,
				mfast::value_storage *storage,
				instruction_cptr      instruction);

			template <typename Visitor>
			void accept(Visitor &v);

			mfast::decimal_mref set_bid_price() const;
		};

		typedef mfast::make_sequence_mref<best_bid_vols_element_mref>
		best_bid_vols_mref;
		best_bid_vols_mref set_best_bid_vols() const;
		mfast::decimal_mref set_bestask_order_price() const;

		class best_ask_vols_element_mref
			: public mfast::make_aggregate_mref<dcel2_MD10Entrust_cref::best_ask_vols_element_cref>
		{
			typedef mfast::make_aggregate_mref<dcel2_MD10Entrust_cref::best_ask_vols_element_cref>
			base_type;
		public:
			best_ask_vols_element_mref(
				mfast::allocator     *alloc,
				mfast::value_storage *storage,
				instruction_cptr      instruction);

			template <typename Visitor>
			void accept(Visitor &v);

			mfast::decimal_mref set_ask_price() const;
		};

		typedef mfast::make_sequence_mref<best_ask_vols_element_mref>
		best_ask_vols_mref;
		best_ask_vols_mref set_best_ask_vols() const;
		mfast::ascii_string_mref set_gentime() const;
	};

	class dcel2_MD10Entrust
		: private mfast::value_storage_array<9>
		, public mfast::message_type
	{
		typedef mfast::message_type base_type;
	public:
		enum {
			the_id = 4
		};
		typedef mfast::template_instruction_ex<dcel2_MD10Entrust_cref> instruction_type;

		typedef mfast::make_message_cref<dcel2_MD10Entrust_cref, instruction_type>
		cref_type;
		typedef mfast::make_message_mref<dcel2_MD10Entrust_mref, instruction_type>
		mref_type;
		dcel2_MD10Entrust(
			mfast::allocator *alloc=mfast::malloc_allocator::instance());
		dcel2_MD10Entrust(
			const dcel2_MD10Entrust_cref &other,
			mfast::allocator *alloc=mfast::malloc_allocator::instance());
		cref_type ref() const;
		cref_type cref() const;
		mref_type ref();
		mref_type mref();
		static const instruction_type *instruction();
	private:
		dcel2_MD10Entrust(const dcel2_MD10Entrust &);
		dcel2_MD10Entrust &operator = (const dcel2_MD10Entrust &);
	};


	class dcel2_MDOrderStat_cref
		: public mfast::aggregate_cref
	{
		typedef mfast::aggregate_cref base_type;
	public:
		typedef mfast::template_instruction_ex<dcel2_MDOrderStat_cref> instruction_type;
		typedef const instruction_type *instruction_cptr;
		dcel2_MDOrderStat_cref();
		template <typename T>
		dcel2_MDOrderStat_cref(
			typename std::enable_if<std::is_same<typename T::cref_type, dcel2_MDOrderStat_cref>::value, const mfast::value_storage *>::type
			storage,
			const T *instruction);

		dcel2_MDOrderStat_cref(const mfast::message_cref &other);

		explicit dcel2_MDOrderStat_cref(const mfast::field_cref &other);

		operator mfast::message_cref();
		template <typename Visitor>
		void accept(Visitor &v);

		mfast::int32_cref get_version() const;
		mfast::int32_cref try_get_version() const;
		mfast::int32_cref get_type() const;
		mfast::int32_cref try_get_type() const;
		mfast::uint32_cref get_length() const;
		mfast::uint32_cref try_get_length() const;
		mfast::ascii_string_cref get_contract() const;
		mfast::ascii_string_cref try_get_contract() const;
		mfast::uint32_cref get_tot_bid_order_qt() const;
		mfast::uint32_cref try_get_tot_bid_order_qt() const;
		mfast::uint32_cref get_tot_ask_order_qt() const;
		mfast::uint32_cref try_get_tot_ask_order_qt() const;
		mfast::decimal_cref get_wavg_bid_order_price() const;
		mfast::decimal_cref try_get_wavg_bid_order_price() const;
		mfast::decimal_cref get_wavg_ask_order_price() const;
		mfast::decimal_cref try_get_wavg_ask_order_price() const;

	};


	typedef mfast::make_aggregate_mref<dcel2_MDOrderStat_cref>
	dcel2_MDOrderStat_mref_base;
	class dcel2_MDOrderStat_mref
		: public dcel2_MDOrderStat_mref_base
	{
		typedef dcel2_MDOrderStat_mref_base base_type;
	public:
		typedef mfast::template_instruction_ex<dcel2_MDOrderStat_cref> instruction_type;
		typedef const instruction_type *instruction_cptr;
		dcel2_MDOrderStat_mref();
		template <typename T>
		dcel2_MDOrderStat_mref(
			mfast::allocator       *alloc,
			typename std::enable_if<std::is_same<typename T::cref_type, dcel2_MDOrderStat_cref>::value, mfast::value_storage *>::type
			storage,
			const T *instruction);

		dcel2_MDOrderStat_mref(const mfast::message_mref &other);

		operator mfast::message_mref();
		explicit dcel2_MDOrderStat_mref(const mfast::field_mref_base &other);

		template <typename Visitor>
		void accept(Visitor &v);

		mfast::int32_mref set_version() const;
		mfast::int32_mref set_type() const;
		mfast::uint32_mref set_length() const;
		mfast::ascii_string_mref set_contract() const;
		mfast::uint32_mref set_tot_bid_order_qt() const;
		mfast::uint32_mref set_tot_ask_order_qt() const;
		mfast::decimal_mref set_wavg_bid_order_price() const;
		mfast::decimal_mref set_wavg_ask_order_price() const;
	};

	class dcel2_MDOrderStat
		: private mfast::value_storage_array<8>
		, public mfast::message_type
	{
		typedef mfast::message_type base_type;
	public:
		enum {
			the_id = 5
		};
		typedef mfast::template_instruction_ex<dcel2_MDOrderStat_cref> instruction_type;

		typedef mfast::make_message_cref<dcel2_MDOrderStat_cref, instruction_type>
		cref_type;
		typedef mfast::make_message_mref<dcel2_MDOrderStat_mref, instruction_type>
		mref_type;
		dcel2_MDOrderStat(
			mfast::allocator *alloc=mfast::malloc_allocator::instance());
		dcel2_MDOrderStat(
			const dcel2_MDOrderStat_cref &other,
			mfast::allocator *alloc=mfast::malloc_allocator::instance());
		cref_type ref() const;
		cref_type cref() const;
		mref_type ref();
		mref_type mref();
		static const instruction_type *instruction();
	private:
		dcel2_MDOrderStat(const dcel2_MDOrderStat &);
		dcel2_MDOrderStat &operator = (const dcel2_MDOrderStat &);
	};


	class dcel2_MDRTPrice_cref
		: public mfast::aggregate_cref
	{
		typedef mfast::aggregate_cref base_type;
	public:
		typedef mfast::template_instruction_ex<dcel2_MDRTPrice_cref> instruction_type;
		typedef const instruction_type *instruction_cptr;
		dcel2_MDRTPrice_cref();
		template <typename T>
		dcel2_MDRTPrice_cref(
			typename std::enable_if<std::is_same<typename T::cref_type, dcel2_MDRTPrice_cref>::value, const mfast::value_storage *>::type
			storage,
			const T *instruction);

		dcel2_MDRTPrice_cref(const mfast::message_cref &other);

		explicit dcel2_MDRTPrice_cref(const mfast::field_cref &other);

		operator mfast::message_cref();
		template <typename Visitor>
		void accept(Visitor &v);

		mfast::int32_cref get_version() const;
		mfast::int32_cref try_get_version() const;
		mfast::int32_cref get_type() const;
		mfast::int32_cref try_get_type() const;
		mfast::uint32_cref get_length() const;
		mfast::uint32_cref try_get_length() const;
		mfast::ascii_string_cref get_contract() const;
		mfast::ascii_string_cref try_get_contract() const;
		mfast::decimal_cref get_rt_price() const;
		mfast::decimal_cref try_get_rt_price() const;

	};


	typedef mfast::make_aggregate_mref<dcel2_MDRTPrice_cref>
	dcel2_MDRTPrice_mref_base;
	class dcel2_MDRTPrice_mref
		: public dcel2_MDRTPrice_mref_base
	{
		typedef dcel2_MDRTPrice_mref_base base_type;
	public:
		typedef mfast::template_instruction_ex<dcel2_MDRTPrice_cref> instruction_type;
		typedef const instruction_type *instruction_cptr;
		dcel2_MDRTPrice_mref();
		template <typename T>
		dcel2_MDRTPrice_mref(
			mfast::allocator       *alloc,
			typename std::enable_if<std::is_same<typename T::cref_type, dcel2_MDRTPrice_cref>::value, mfast::value_storage *>::type
			storage,
			const T *instruction);

		dcel2_MDRTPrice_mref(const mfast::message_mref &other);

		operator mfast::message_mref();
		explicit dcel2_MDRTPrice_mref(const mfast::field_mref_base &other);

		template <typename Visitor>
		void accept(Visitor &v);

		mfast::int32_mref set_version() const;
		mfast::int32_mref set_type() const;
		mfast::uint32_mref set_length() const;
		mfast::ascii_string_mref set_contract() const;
		mfast::decimal_mref set_rt_price() const;
	};

	class dcel2_MDRTPrice
		: private mfast::value_storage_array<5>
		, public mfast::message_type
	{
		typedef mfast::message_type base_type;
	public:
		enum {
			the_id = 6
		};
		typedef mfast::template_instruction_ex<dcel2_MDRTPrice_cref> instruction_type;

		typedef mfast::make_message_cref<dcel2_MDRTPrice_cref, instruction_type>
		cref_type;
		typedef mfast::make_message_mref<dcel2_MDRTPrice_mref, instruction_type>
		mref_type;
		dcel2_MDRTPrice(
			mfast::allocator *alloc=mfast::malloc_allocator::instance());
		dcel2_MDRTPrice(
			const dcel2_MDRTPrice_cref &other,
			mfast::allocator *alloc=mfast::malloc_allocator::instance());
		cref_type ref() const;
		cref_type cref() const;
		mref_type ref();
		mref_type mref();
		static const instruction_type *instruction();
	private:
		dcel2_MDRTPrice(const dcel2_MDRTPrice &);
		dcel2_MDRTPrice &operator = (const dcel2_MDRTPrice &);
	};


	class dcel2_MDMatchPV_cref
		: public mfast::aggregate_cref
	{
		typedef mfast::aggregate_cref base_type;
	public:
		typedef mfast::template_instruction_ex<dcel2_MDMatchPV_cref> instruction_type;
		typedef const instruction_type *instruction_cptr;
		dcel2_MDMatchPV_cref();
		template <typename T>
		dcel2_MDMatchPV_cref(
			typename std::enable_if<std::is_same<typename T::cref_type, dcel2_MDMatchPV_cref>::value, const mfast::value_storage *>::type
			storage,
			const T *instruction);

		dcel2_MDMatchPV_cref(const mfast::message_cref &other);

		explicit dcel2_MDMatchPV_cref(const mfast::field_cref &other);

		operator mfast::message_cref();
		template <typename Visitor>
		void accept(Visitor &v);

		mfast::int32_cref get_version() const;
		mfast::int32_cref try_get_version() const;
		mfast::int32_cref get_type() const;
		mfast::int32_cref try_get_type() const;
		mfast::uint32_cref get_length() const;
		mfast::uint32_cref try_get_length() const;
		mfast::ascii_string_cref get_contract() const;
		mfast::ascii_string_cref try_get_contract() const;

		class bs_vols_element_cref
			: public mfast::sequence_element_cref
		{
			typedef mfast::sequence_element_cref base_type;
		public:
			typedef mfast::sequence_instruction_ex<bs_vols_element_cref> instruction_type;
			typedef const instruction_type *instruction_cptr;
			bs_vols_element_cref(
				const mfast::value_storage *storage,
				instruction_cptr            instruction);

			template <typename Visitor>
			void accept(Visitor &v);

			mfast::decimal_cref get_level_price() const;
			mfast::decimal_cref try_get_level_price() const;
			mfast::int32_cref get_bo_vol() const;
			mfast::int32_cref try_get_bo_vol() const;
			mfast::int32_cref get_be_vol() const;
			mfast::int32_cref try_get_be_vol() const;
			mfast::int32_cref get_so_vol() const;
			mfast::int32_cref try_get_so_vol() const;
			mfast::int32_cref get_se_vol() const;
			mfast::int32_cref try_get_se_vol() const;
		};

		typedef mfast::make_sequence_cref<bs_vols_element_cref> bs_vols_cref;
		bs_vols_cref get_bs_vols() const;
		bs_vols_cref try_get_bs_vols() const;

	};


	typedef mfast::make_aggregate_mref<dcel2_MDMatchPV_cref>
	dcel2_MDMatchPV_mref_base;
	class dcel2_MDMatchPV_mref
		: public dcel2_MDMatchPV_mref_base
	{
		typedef dcel2_MDMatchPV_mref_base base_type;
	public:
		typedef mfast::template_instruction_ex<dcel2_MDMatchPV_cref> instruction_type;
		typedef const instruction_type *instruction_cptr;
		dcel2_MDMatchPV_mref();
		template <typename T>
		dcel2_MDMatchPV_mref(
			mfast::allocator       *alloc,
			typename std::enable_if<std::is_same<typename T::cref_type, dcel2_MDMatchPV_cref>::value, mfast::value_storage *>::type
			storage,
			const T *instruction);

		dcel2_MDMatchPV_mref(const mfast::message_mref &other);

		operator mfast::message_mref();
		explicit dcel2_MDMatchPV_mref(const mfast::field_mref_base &other);

		template <typename Visitor>
		void accept(Visitor &v);

		mfast::int32_mref set_version() const;
		mfast::int32_mref set_type() const;
		mfast::uint32_mref set_length() const;
		mfast::ascii_string_mref set_contract() const;

		class bs_vols_element_mref
			: public mfast::make_aggregate_mref<dcel2_MDMatchPV_cref::bs_vols_element_cref>
		{
			typedef mfast::make_aggregate_mref<dcel2_MDMatchPV_cref::bs_vols_element_cref>
			base_type;
		public:
			bs_vols_element_mref(
				mfast::allocator     *alloc,
				mfast::value_storage *storage,
				instruction_cptr      instruction);

			template <typename Visitor>
			void accept(Visitor &v);

			mfast::decimal_mref set_level_price() const;
			mfast::int32_mref set_bo_vol() const;
			mfast::int32_mref set_be_vol() const;
			mfast::int32_mref set_so_vol() const;
			mfast::int32_mref set_se_vol() const;
		};

		typedef mfast::make_sequence_mref<bs_vols_element_mref> bs_vols_mref;
		bs_vols_mref set_bs_vols() const;
	};

	class dcel2_MDMatchPV
		: private mfast::value_storage_array<5>
		, public mfast::message_type
	{
		typedef mfast::message_type base_type;
	public:
		enum {
			the_id = 7
		};
		typedef mfast::template_instruction_ex<dcel2_MDMatchPV_cref> instruction_type;

		typedef mfast::make_message_cref<dcel2_MDMatchPV_cref, instruction_type>
		cref_type;
		typedef mfast::make_message_mref<dcel2_MDMatchPV_mref, instruction_type>
		mref_type;
		dcel2_MDMatchPV(
			mfast::allocator *alloc=mfast::malloc_allocator::instance());
		dcel2_MDMatchPV(
			const dcel2_MDMatchPV_cref &other,
			mfast::allocator *alloc=mfast::malloc_allocator::instance());
		cref_type ref() const;
		cref_type cref() const;
		mref_type ref();
		mref_type mref();
		static const instruction_type *instruction();
	private:
		dcel2_MDMatchPV(const dcel2_MDMatchPV &);
		dcel2_MDMatchPV &operator = (const dcel2_MDMatchPV &);
	};


	class zcel2_Snapshot_cref
		: public mfast::aggregate_cref
	{
		typedef mfast::aggregate_cref base_type;
	public:
		typedef mfast::template_instruction_ex<zcel2_Snapshot_cref> instruction_type;
		typedef const instruction_type *instruction_cptr;
		zcel2_Snapshot_cref();
		template <typename T>
		zcel2_Snapshot_cref(
			typename std::enable_if<std::is_same<typename T::cref_type, zcel2_Snapshot_cref>::value, const mfast::value_storage *>::type
			storage,
			const T *instruction);

		zcel2_Snapshot_cref(const mfast::message_cref &other);

		explicit zcel2_Snapshot_cref(const mfast::field_cref &other);

		operator mfast::message_cref();
		template <typename Visitor>
		void accept(Visitor &v);

		mfast::int32_cref get_protocol_ver() const;
		mfast::int32_cref try_get_protocol_ver() const;
		mfast::ascii_string_cref get_contract() const;
		mfast::ascii_string_cref try_get_contract() const;
		mfast::int32_cref get_type() const;
		mfast::int32_cref try_get_type() const;
		mfast::decimal_cref get_pre_settlement_price() const;
		mfast::decimal_cref try_get_pre_settlement_price() const;
		mfast::decimal_cref get_pre_close_price() const;
		mfast::decimal_cref try_get_pre_close_price() const;
		mfast::decimal_cref get_pre_open_interest() const;
		mfast::decimal_cref try_get_pre_open_interest() const;
		mfast::decimal_cref get_open_price() const;
		mfast::decimal_cref try_get_open_price() const;
		mfast::decimal_cref get_high_price() const;
		mfast::decimal_cref try_get_high_price() const;
		mfast::decimal_cref get_low_price() const;
		mfast::decimal_cref try_get_low_price() const;
		mfast::decimal_cref get_last_price() const;
		mfast::decimal_cref try_get_last_price() const;

		class bid_ask_pvs_element_cref
			: public mfast::sequence_element_cref
		{
			typedef mfast::sequence_element_cref base_type;
		public:
			typedef mfast::sequence_instruction_ex<bid_ask_pvs_element_cref>
			instruction_type;
			typedef const instruction_type *instruction_cptr;
			bid_ask_pvs_element_cref(
				const mfast::value_storage *storage,
				instruction_cptr            instruction);

			template <typename Visitor>
			void accept(Visitor &v);

			mfast::decimal_cref get_level_price() const;
			mfast::decimal_cref try_get_level_price() const;
			mfast::int32_cref get_level_vol() const;
			mfast::int32_cref try_get_level_vol() const;
		};

		typedef mfast::make_sequence_cref<bid_ask_pvs_element_cref> bid_ask_pvs_cref;
		bid_ask_pvs_cref get_bid_ask_pvs() const;
		bid_ask_pvs_cref try_get_bid_ask_pvs() const;
		mfast::int32_cref get_total_volme() const;
		mfast::int32_cref try_get_total_volme() const;
		mfast::int32_cref get_open_interest() const;
		mfast::int32_cref try_get_open_interest() const;
		mfast::decimal_cref get_close_price() const;
		mfast::decimal_cref try_get_close_price() const;
		mfast::decimal_cref get_settlement_price() const;
		mfast::decimal_cref try_get_settlement_price() const;
		mfast::decimal_cref get_avg_price() const;
		mfast::decimal_cref try_get_avg_price() const;
		mfast::decimal_cref get_life_high_price() const;
		mfast::decimal_cref try_get_life_high_price() const;
		mfast::decimal_cref get_life_low_price() const;
		mfast::decimal_cref try_get_life_low_price() const;
		mfast::decimal_cref get_high_limit_price() const;
		mfast::decimal_cref try_get_high_limit_price() const;
		mfast::decimal_cref get_low_limit_price() const;
		mfast::decimal_cref try_get_low_limit_price() const;
		mfast::decimal_cref get_total_bid_vol() const;
		mfast::decimal_cref try_get_total_bid_vol() const;
		mfast::decimal_cref get_total_ask_vol() const;
		mfast::decimal_cref try_get_total_ask_vol() const;
		mfast::ascii_string_cref get_timestamp() const;
		mfast::ascii_string_cref try_get_timestamp() const;

	};


	typedef mfast::make_aggregate_mref<zcel2_Snapshot_cref>
	zcel2_Snapshot_mref_base;
	class zcel2_Snapshot_mref
		: public zcel2_Snapshot_mref_base
	{
		typedef zcel2_Snapshot_mref_base base_type;
	public:
		typedef mfast::template_instruction_ex<zcel2_Snapshot_cref> instruction_type;
		typedef const instruction_type *instruction_cptr;
		zcel2_Snapshot_mref();
		template <typename T>
		zcel2_Snapshot_mref(
			mfast::allocator       *alloc,
			typename std::enable_if<std::is_same<typename T::cref_type, zcel2_Snapshot_cref>::value, mfast::value_storage *>::type
			storage,
			const T *instruction);

		zcel2_Snapshot_mref(const mfast::message_mref &other);

		operator mfast::message_mref();
		explicit zcel2_Snapshot_mref(const mfast::field_mref_base &other);

		template <typename Visitor>
		void accept(Visitor &v);

		mfast::int32_mref set_protocol_ver() const;
		mfast::ascii_string_mref set_contract() const;
		mfast::int32_mref set_type() const;
		mfast::decimal_mref set_pre_settlement_price() const;
		mfast::decimal_mref set_pre_close_price() const;
		mfast::decimal_mref set_pre_open_interest() const;
		mfast::decimal_mref set_open_price() const;
		mfast::decimal_mref set_high_price() const;
		mfast::decimal_mref set_low_price() const;
		mfast::decimal_mref set_last_price() const;

		class bid_ask_pvs_element_mref
			: public mfast::make_aggregate_mref<zcel2_Snapshot_cref::bid_ask_pvs_element_cref>
		{
			typedef mfast::make_aggregate_mref<zcel2_Snapshot_cref::bid_ask_pvs_element_cref>
			base_type;
		public:
			bid_ask_pvs_element_mref(
				mfast::allocator     *alloc,
				mfast::value_storage *storage,
				instruction_cptr      instruction);

			template <typename Visitor>
			void accept(Visitor &v);

			mfast::decimal_mref set_level_price() const;
			mfast::int32_mref set_level_vol() const;
		};

		typedef mfast::make_sequence_mref<bid_ask_pvs_element_mref> bid_ask_pvs_mref;
		bid_ask_pvs_mref set_bid_ask_pvs() const;
		mfast::int32_mref set_total_volme() const;
		mfast::int32_mref set_open_interest() const;
		mfast::decimal_mref set_close_price() const;
		mfast::decimal_mref set_settlement_price() const;
		mfast::decimal_mref set_avg_price() const;
		mfast::decimal_mref set_life_high_price() const;
		mfast::decimal_mref set_life_low_price() const;
		mfast::decimal_mref set_high_limit_price() const;
		mfast::decimal_mref set_low_limit_price() const;
		mfast::decimal_mref set_total_bid_vol() const;
		mfast::decimal_mref set_total_ask_vol() const;
		mfast::ascii_string_mref set_timestamp() const;
	};

	class zcel2_Snapshot
		: private mfast::value_storage_array<23>
		, public mfast::message_type
	{
		typedef mfast::message_type base_type;
	public:
		enum {
			the_id = 16
		};
		typedef mfast::template_instruction_ex<zcel2_Snapshot_cref> instruction_type;

		typedef mfast::make_message_cref<zcel2_Snapshot_cref, instruction_type>
		cref_type;
		typedef mfast::make_message_mref<zcel2_Snapshot_mref, instruction_type>
		mref_type;
		zcel2_Snapshot(
			mfast::allocator *alloc=mfast::malloc_allocator::instance());
		zcel2_Snapshot(
			const zcel2_Snapshot_cref &other,
			mfast::allocator *alloc=mfast::malloc_allocator::instance());
		cref_type ref() const;
		cref_type cref() const;
		mref_type ref();
		mref_type mref();
		static const instruction_type *instruction();
	private:
		zcel2_Snapshot(const zcel2_Snapshot &);
		zcel2_Snapshot &operator = (const zcel2_Snapshot &);
	};


	class zcel2_CMB_cref
		: public mfast::aggregate_cref
	{
		typedef mfast::aggregate_cref base_type;
	public:
		typedef mfast::template_instruction_ex<zcel2_CMB_cref> instruction_type;
		typedef const instruction_type *instruction_cptr;
		zcel2_CMB_cref();
		template <typename T>
		zcel2_CMB_cref(
			typename std::enable_if<std::is_same<typename T::cref_type, zcel2_CMB_cref>::value, const mfast::value_storage *>::type
			storage,
			const T *instruction);

		zcel2_CMB_cref(const mfast::message_cref &other);

		explicit zcel2_CMB_cref(const mfast::field_cref &other);

		operator mfast::message_cref();
		template <typename Visitor>
		void accept(Visitor &v);

		mfast::int32_cref get_protocol_ver() const;
		mfast::int32_cref try_get_protocol_ver() const;
		mfast::int32_cref get_cmb_type() const;
		mfast::int32_cref try_get_cmb_type() const;
		mfast::ascii_string_cref get_contract() const;
		mfast::ascii_string_cref try_get_contract() const;
		mfast::decimal_cref get_bid_price() const;
		mfast::decimal_cref try_get_bid_price() const;
		mfast::decimal_cref get_ask_price() const;
		mfast::decimal_cref try_get_ask_price() const;
		mfast::int32_cref get_bid_vol() const;
		mfast::int32_cref try_get_bid_vol() const;
		mfast::int32_cref get_ask_vol() const;
		mfast::int32_cref try_get_ask_vol() const;
		mfast::int32_cref get_total_bid_vol() const;
		mfast::int32_cref try_get_total_bid_vol() const;
		mfast::int32_cref get_total_ask_vol() const;
		mfast::int32_cref try_get_total_ask_vol() const;
		mfast::ascii_string_cref get_timestamp() const;
		mfast::ascii_string_cref try_get_timestamp() const;

	};


	typedef mfast::make_aggregate_mref<zcel2_CMB_cref> zcel2_CMB_mref_base;
	class zcel2_CMB_mref
		: public zcel2_CMB_mref_base
	{
		typedef zcel2_CMB_mref_base base_type;
	public:
		typedef mfast::template_instruction_ex<zcel2_CMB_cref> instruction_type;
		typedef const instruction_type *instruction_cptr;
		zcel2_CMB_mref();
		template <typename T>
		zcel2_CMB_mref(
			mfast::allocator       *alloc,
			typename std::enable_if<std::is_same<typename T::cref_type, zcel2_CMB_cref>::value, mfast::value_storage *>::type
			storage,
			const T *instruction);

		zcel2_CMB_mref(const mfast::message_mref &other);

		operator mfast::message_mref();
		explicit zcel2_CMB_mref(const mfast::field_mref_base &other);

		template <typename Visitor>
		void accept(Visitor &v);

		mfast::int32_mref set_protocol_ver() const;
		mfast::int32_mref set_cmb_type() const;
		mfast::ascii_string_mref set_contract() const;
		mfast::decimal_mref set_bid_price() const;
		mfast::decimal_mref set_ask_price() const;
		mfast::int32_mref set_bid_vol() const;
		mfast::int32_mref set_ask_vol() const;
		mfast::int32_mref set_total_bid_vol() const;
		mfast::int32_mref set_total_ask_vol() const;
		mfast::ascii_string_mref set_timestamp() const;
	};

	class zcel2_CMB
		: private mfast::value_storage_array<10>
		, public mfast::message_type
	{
		typedef mfast::message_type base_type;
	public:
		enum {
			the_id = 17
		};
		typedef mfast::template_instruction_ex<zcel2_CMB_cref> instruction_type;

		typedef mfast::make_message_cref<zcel2_CMB_cref, instruction_type> cref_type;
		typedef mfast::make_message_mref<zcel2_CMB_mref, instruction_type> mref_type;
		zcel2_CMB(
			mfast::allocator *alloc=mfast::malloc_allocator::instance());
		zcel2_CMB(
			const zcel2_CMB_cref &other,
			mfast::allocator *alloc=mfast::malloc_allocator::instance());
		cref_type ref() const;
		cref_type cref() const;
		mref_type ref();
		mref_type mref();
		static const instruction_type *instruction();
	private:
		zcel2_CMB(const zcel2_CMB &);
		zcel2_CMB &operator = (const zcel2_CMB &);
	};


	class level1_cref
		: public mfast::aggregate_cref
	{
		typedef mfast::aggregate_cref base_type;
	public:
		typedef mfast::template_instruction_ex<level1_cref> instruction_type;
		typedef const instruction_type *instruction_cptr;
		level1_cref();
		template <typename T>
		level1_cref(
			typename std::enable_if<std::is_same<typename T::cref_type, level1_cref>::value, const mfast::value_storage *>::type
			storage,
			const T *instruction);

		level1_cref(const mfast::message_cref &other);

		explicit level1_cref(const mfast::field_cref &other);

		operator mfast::message_cref();
		template <typename Visitor>
		void accept(Visitor &v);

		mfast::int32_cref get_protocol_ver() const;
		mfast::int32_cref try_get_protocol_ver() const;
		mfast::uint64_cref get_timestamp() const;
		mfast::uint64_cref try_get_timestamp() const;
		mfast::ascii_string_cref get_trading_day() const;
		mfast::ascii_string_cref try_get_trading_day() const;
		mfast::ascii_string_cref get_settlement_GID() const;
		mfast::ascii_string_cref try_get_settlement_GID() const;
		mfast::int32_cref get_settlement_ID() const;
		mfast::int32_cref try_get_settlement_ID() const;
		mfast::decimal_cref get_last_price() const;
		mfast::decimal_cref try_get_last_price() const;
		mfast::decimal_cref get_pre_settlement_price() const;
		mfast::decimal_cref try_get_pre_settlement_price() const;
		mfast::decimal_cref get_pre_close_price() const;
		mfast::decimal_cref try_get_pre_close_price() const;
		mfast::decimal_cref get_pre_open_interest() const;
		mfast::decimal_cref try_get_pre_open_interest() const;
		mfast::decimal_cref get_open_price() const;
		mfast::decimal_cref try_get_open_price() const;
		mfast::decimal_cref get_highest_price() const;
		mfast::decimal_cref try_get_highest_price() const;
		mfast::decimal_cref get_lowest_price() const;
		mfast::decimal_cref try_get_lowest_price() const;
		mfast::int32_cref get_total_volume() const;
		mfast::int32_cref try_get_total_volume() const;
		mfast::decimal_cref get_total_turnover() const;
		mfast::decimal_cref try_get_total_turnover() const;
		mfast::decimal_cref get_open_interest() const;
		mfast::decimal_cref try_get_open_interest() const;
		mfast::decimal_cref get_close_price() const;
		mfast::decimal_cref try_get_close_price() const;
		mfast::decimal_cref get_settlement_price() const;
		mfast::decimal_cref try_get_settlement_price() const;
		mfast::decimal_cref get_upper_limit_price() const;
		mfast::decimal_cref try_get_upper_limit_price() const;
		mfast::decimal_cref get_lower_limit_price() const;
		mfast::decimal_cref try_get_lower_limit_price() const;
		mfast::decimal_cref get_pre_delta() const;
		mfast::decimal_cref try_get_pre_delta() const;
		mfast::decimal_cref get_cur_delta() const;
		mfast::decimal_cref try_get_cur_delta() const;
		mfast::ascii_string_cref get_update_time() const;
		mfast::ascii_string_cref try_get_update_time() const;
		mfast::int32_cref get_update_ms() const;
		mfast::int32_cref try_get_update_ms() const;
		mfast::ascii_string_cref get_instrument_id() const;
		mfast::ascii_string_cref try_get_instrument_id() const;

		class bid_ask_pvs_element_cref
			: public mfast::sequence_element_cref
		{
			typedef mfast::sequence_element_cref base_type;
		public:
			typedef mfast::sequence_instruction_ex<bid_ask_pvs_element_cref>
			instruction_type;
			typedef const instruction_type *instruction_cptr;
			bid_ask_pvs_element_cref(
				const mfast::value_storage *storage,
				instruction_cptr            instruction);

			template <typename Visitor>
			void accept(Visitor &v);

			mfast::decimal_cref get_level_price() const;
			mfast::decimal_cref try_get_level_price() const;
			mfast::int32_cref get_level_vol() const;
			mfast::int32_cref try_get_level_vol() const;
		};

		typedef mfast::make_sequence_cref<bid_ask_pvs_element_cref> bid_ask_pvs_cref;
		bid_ask_pvs_cref get_bid_ask_pvs() const;
		bid_ask_pvs_cref try_get_bid_ask_pvs() const;
		mfast::ascii_string_cref get_action_day() const;
		mfast::ascii_string_cref try_get_action_day() const;

	};


	typedef mfast::make_aggregate_mref<level1_cref> level1_mref_base;
	class level1_mref
		: public level1_mref_base
	{
		typedef level1_mref_base base_type;
	public:
		typedef mfast::template_instruction_ex<level1_cref> instruction_type;
		typedef const instruction_type *instruction_cptr;
		level1_mref();
		template <typename T>
		level1_mref(
			mfast::allocator       *alloc,
			typename std::enable_if<std::is_same<typename T::cref_type, level1_cref>::value, mfast::value_storage *>::type
			storage,
			const T *instruction);

		level1_mref(const mfast::message_mref &other);

		operator mfast::message_mref();
		explicit level1_mref(const mfast::field_mref_base &other);

		template <typename Visitor>
		void accept(Visitor &v);

		mfast::int32_mref set_protocol_ver() const;
		mfast::uint64_mref set_timestamp() const;
		mfast::ascii_string_mref set_trading_day() const;
		mfast::ascii_string_mref set_settlement_GID() const;
		mfast::int32_mref set_settlement_ID() const;
		mfast::decimal_mref set_last_price() const;
		mfast::decimal_mref set_pre_settlement_price() const;
		mfast::decimal_mref set_pre_close_price() const;
		mfast::decimal_mref set_pre_open_interest() const;
		mfast::decimal_mref set_open_price() const;
		mfast::decimal_mref set_highest_price() const;
		mfast::decimal_mref set_lowest_price() const;
		mfast::int32_mref set_total_volume() const;
		mfast::decimal_mref set_total_turnover() const;
		mfast::decimal_mref set_open_interest() const;
		mfast::decimal_mref set_close_price() const;
		mfast::decimal_mref set_settlement_price() const;
		mfast::decimal_mref set_upper_limit_price() const;
		mfast::decimal_mref set_lower_limit_price() const;
		mfast::decimal_mref set_pre_delta() const;
		mfast::decimal_mref set_cur_delta() const;
		mfast::ascii_string_mref set_update_time() const;
		mfast::int32_mref set_update_ms() const;
		mfast::ascii_string_mref set_instrument_id() const;

		class bid_ask_pvs_element_mref
			: public mfast::make_aggregate_mref<level1_cref::bid_ask_pvs_element_cref>
		{
			typedef mfast::make_aggregate_mref<level1_cref::bid_ask_pvs_element_cref>
			base_type;
		public:
			bid_ask_pvs_element_mref(
				mfast::allocator     *alloc,
				mfast::value_storage *storage,
				instruction_cptr      instruction);

			template <typename Visitor>
			void accept(Visitor &v);

			mfast::decimal_mref set_level_price() const;
			mfast::int32_mref set_level_vol() const;
		};

		typedef mfast::make_sequence_mref<bid_ask_pvs_element_mref> bid_ask_pvs_mref;
		bid_ask_pvs_mref set_bid_ask_pvs() const;
		mfast::ascii_string_mref set_action_day() const;
	};

	class level1
		: private mfast::value_storage_array<26>
		, public mfast::message_type
	{
		typedef mfast::message_type base_type;
	public:
		enum {
			the_id = 10
		};
		typedef mfast::template_instruction_ex<level1_cref> instruction_type;

		typedef mfast::make_message_cref<level1_cref, instruction_type> cref_type;
		typedef mfast::make_message_mref<level1_mref, instruction_type> mref_type;
		level1(
			mfast::allocator *alloc=mfast::malloc_allocator::instance());
		level1(
			const level1_cref &other,
			mfast::allocator *alloc=mfast::malloc_allocator::instance());
		cref_type ref() const;
		cref_type cref() const;
		mref_type ref();
		mref_type mref();
		static const instruction_type *instruction();
	private:
		level1(const level1 &);
		level1 &operator = (const level1 &);
	};


	class stock_TdfMarketl2_cref
		: public mfast::aggregate_cref
	{
		typedef mfast::aggregate_cref base_type;
	public:
		typedef mfast::template_instruction_ex<stock_TdfMarketl2_cref> instruction_type;
		typedef const instruction_type *instruction_cptr;
		stock_TdfMarketl2_cref();
		template <typename T>
		stock_TdfMarketl2_cref(
			typename std::enable_if<std::is_same<typename T::cref_type, stock_TdfMarketl2_cref>::value, const mfast::value_storage *>::type
			storage,
			const T *instruction);

		stock_TdfMarketl2_cref(const mfast::message_cref &other);

		explicit stock_TdfMarketl2_cref(const mfast::field_cref &other);

		operator mfast::message_cref();
		template <typename Visitor>
		void accept(Visitor &v);

		mfast::int32_cref get_version() const;
		mfast::int32_cref try_get_version() const;
		mfast::ascii_string_cref get_WIND_code() const;
		mfast::ascii_string_cref try_get_WIND_code() const;
		mfast::ascii_string_cref get_origin_code() const;
		mfast::ascii_string_cref try_get_origin_code() const;
		mfast::int32_cref get_action_day() const;
		mfast::int32_cref try_get_action_day() const;
		mfast::int32_cref get_trading_day() const;
		mfast::int32_cref try_get_trading_day() const;
		mfast::int32_cref get_time() const;
		mfast::int32_cref try_get_time() const;
		mfast::int32_cref get_status() const;
		mfast::int32_cref try_get_status() const;
		mfast::uint32_cref get_pre_close_price() const;
		mfast::uint32_cref try_get_pre_close_price() const;
		mfast::uint32_cref get_open_price() const;
		mfast::uint32_cref try_get_open_price() const;
		mfast::uint32_cref get_highest_price() const;
		mfast::uint32_cref try_get_highest_price() const;
		mfast::uint32_cref get_lowest_price() const;
		mfast::uint32_cref try_get_lowest_price() const;
		mfast::uint32_cref get_match_price() const;
		mfast::uint32_cref try_get_match_price() const;

		class bid_ask_pvs_element_cref
			: public mfast::sequence_element_cref
		{
			typedef mfast::sequence_element_cref base_type;
		public:
			typedef mfast::sequence_instruction_ex<bid_ask_pvs_element_cref>
			instruction_type;
			typedef const instruction_type *instruction_cptr;
			bid_ask_pvs_element_cref(
				const mfast::value_storage *storage,
				instruction_cptr            instruction);

			template <typename Visitor>
			void accept(Visitor &v);

			mfast::uint32_cref get_level_price() const;
			mfast::uint32_cref try_get_level_price() const;
			mfast::uint32_cref get_level_vol() const;
			mfast::uint32_cref try_get_level_vol() const;
		};

		typedef mfast::make_sequence_cref<bid_ask_pvs_element_cref> bid_ask_pvs_cref;
		bid_ask_pvs_cref get_bid_ask_pvs() const;
		bid_ask_pvs_cref try_get_bid_ask_pvs() const;
		mfast::uint32_cref get_trade_qt() const;
		mfast::uint32_cref try_get_trade_qt() const;
		mfast::int64_cref get_total_vol() const;
		mfast::int64_cref try_get_total_vol() const;
		mfast::int64_cref get_total_turnover() const;
		mfast::int64_cref try_get_total_turnover() const;
		mfast::int64_cref get_total_bid_vol() const;
		mfast::int64_cref try_get_total_bid_vol() const;
		mfast::int64_cref get_total_ask_vol() const;
		mfast::int64_cref try_get_total_ask_vol() const;
		mfast::uint32_cref get_w_avg_bid_price() const;
		mfast::uint32_cref try_get_w_avg_bid_price() const;
		mfast::uint32_cref get_w_avg_ask_price() const;
		mfast::uint32_cref try_get_w_avg_ask_price() const;
		mfast::int32_cref get_iopv() const;
		mfast::int32_cref try_get_iopv() const;
		mfast::int32_cref get_yield_to_maturity() const;
		mfast::int32_cref try_get_yield_to_maturity() const;
		mfast::uint32_cref get_upper_limit_price() const;
		mfast::uint32_cref try_get_upper_limit_price() const;
		mfast::uint32_cref get_lower_limit_price() const;
		mfast::uint32_cref try_get_lower_limit_price() const;
		mfast::ascii_string_cref get_prefix() const;
		mfast::ascii_string_cref try_get_prefix() const;
		mfast::int32_cref get_pe_ratio1() const;
		mfast::int32_cref try_get_pe_ratio1() const;
		mfast::int32_cref get_pe_ratio2() const;
		mfast::int32_cref try_get_pe_ratio2() const;
		mfast::int32_cref get_net_change2() const;
		mfast::int32_cref try_get_net_change2() const;

	};


	typedef mfast::make_aggregate_mref<stock_TdfMarketl2_cref>
	stock_TdfMarketl2_mref_base;
	class stock_TdfMarketl2_mref
		: public stock_TdfMarketl2_mref_base
	{
		typedef stock_TdfMarketl2_mref_base base_type;
	public:
		typedef mfast::template_instruction_ex<stock_TdfMarketl2_cref> instruction_type;
		typedef const instruction_type *instruction_cptr;
		stock_TdfMarketl2_mref();
		template <typename T>
		stock_TdfMarketl2_mref(
			mfast::allocator       *alloc,
			typename std::enable_if<std::is_same<typename T::cref_type, stock_TdfMarketl2_cref>::value, mfast::value_storage *>::type
			storage,
			const T *instruction);

		stock_TdfMarketl2_mref(const mfast::message_mref &other);

		operator mfast::message_mref();
		explicit stock_TdfMarketl2_mref(const mfast::field_mref_base &other);

		template <typename Visitor>
		void accept(Visitor &v);

		mfast::int32_mref set_version() const;
		mfast::ascii_string_mref set_WIND_code() const;
		mfast::ascii_string_mref set_origin_code() const;
		mfast::int32_mref set_action_day() const;
		mfast::int32_mref set_trading_day() const;
		mfast::int32_mref set_time() const;
		mfast::int32_mref set_status() const;
		mfast::uint32_mref set_pre_close_price() const;
		mfast::uint32_mref set_open_price() const;
		mfast::uint32_mref set_highest_price() const;
		mfast::uint32_mref set_lowest_price() const;
		mfast::uint32_mref set_match_price() const;

		class bid_ask_pvs_element_mref
			: public mfast::make_aggregate_mref<stock_TdfMarketl2_cref::bid_ask_pvs_element_cref>
		{
			typedef mfast::make_aggregate_mref<stock_TdfMarketl2_cref::bid_ask_pvs_element_cref>
			base_type;
		public:
			bid_ask_pvs_element_mref(
				mfast::allocator     *alloc,
				mfast::value_storage *storage,
				instruction_cptr      instruction);

			template <typename Visitor>
			void accept(Visitor &v);

			mfast::uint32_mref set_level_price() const;
			mfast::uint32_mref set_level_vol() const;
		};

		typedef mfast::make_sequence_mref<bid_ask_pvs_element_mref> bid_ask_pvs_mref;
		bid_ask_pvs_mref set_bid_ask_pvs() const;
		mfast::uint32_mref set_trade_qt() const;
		mfast::int64_mref set_total_vol() const;
		mfast::int64_mref set_total_turnover() const;
		mfast::int64_mref set_total_bid_vol() const;
		mfast::int64_mref set_total_ask_vol() const;
		mfast::uint32_mref set_w_avg_bid_price() const;
		mfast::uint32_mref set_w_avg_ask_price() const;
		mfast::int32_mref set_iopv() const;
		mfast::int32_mref set_yield_to_maturity() const;
		mfast::uint32_mref set_upper_limit_price() const;
		mfast::uint32_mref set_lower_limit_price() const;
		mfast::ascii_string_mref set_prefix() const;
		mfast::int32_mref set_pe_ratio1() const;
		mfast::int32_mref set_pe_ratio2() const;
		mfast::int32_mref set_net_change2() const;
	};

	class stock_TdfMarketl2
		: private mfast::value_storage_array<28>
		, public mfast::message_type
	{
		typedef mfast::message_type base_type;
	public:
		enum {
			the_id = 13
		};
		typedef mfast::template_instruction_ex<stock_TdfMarketl2_cref> instruction_type;

		typedef mfast::make_message_cref<stock_TdfMarketl2_cref, instruction_type>
		cref_type;
		typedef mfast::make_message_mref<stock_TdfMarketl2_mref, instruction_type>
		mref_type;
		stock_TdfMarketl2(
			mfast::allocator *alloc=mfast::malloc_allocator::instance());
		stock_TdfMarketl2(
			const stock_TdfMarketl2_cref &other,
			mfast::allocator *alloc=mfast::malloc_allocator::instance());
		cref_type ref() const;
		cref_type cref() const;
		mref_type ref();
		mref_type mref();
		static const instruction_type *instruction();
	private:
		stock_TdfMarketl2(const stock_TdfMarketl2 &);
		stock_TdfMarketl2 &operator = (const stock_TdfMarketl2 &);
	};


	class stock_TdfIndexl2_cref
		: public mfast::aggregate_cref
	{
		typedef mfast::aggregate_cref base_type;
	public:
		typedef mfast::template_instruction_ex<stock_TdfIndexl2_cref> instruction_type;
		typedef const instruction_type *instruction_cptr;
		stock_TdfIndexl2_cref();
		template <typename T>
		stock_TdfIndexl2_cref(
			typename std::enable_if<std::is_same<typename T::cref_type, stock_TdfIndexl2_cref>::value, const mfast::value_storage *>::type
			storage,
			const T *instruction);

		stock_TdfIndexl2_cref(const mfast::message_cref &other);

		explicit stock_TdfIndexl2_cref(const mfast::field_cref &other);

		operator mfast::message_cref();
		template <typename Visitor>
		void accept(Visitor &v);

		mfast::int32_cref get_version() const;
		mfast::int32_cref try_get_version() const;
		mfast::ascii_string_cref get_WIND_code() const;
		mfast::ascii_string_cref try_get_WIND_code() const;
		mfast::ascii_string_cref get_origin_code() const;
		mfast::ascii_string_cref try_get_origin_code() const;
		mfast::int32_cref get_action_day() const;
		mfast::int32_cref try_get_action_day() const;
		mfast::int32_cref get_trading_day() const;
		mfast::int32_cref try_get_trading_day() const;
		mfast::int32_cref get_time() const;
		mfast::int32_cref try_get_time() const;
		mfast::int32_cref get_open_index() const;
		mfast::int32_cref try_get_open_index() const;
		mfast::int32_cref get_highest_index() const;
		mfast::int32_cref try_get_highest_index() const;
		mfast::int32_cref get_lowest_index() const;
		mfast::int32_cref try_get_lowest_index() const;
		mfast::int32_cref get_last_index() const;
		mfast::int32_cref try_get_last_index() const;
		mfast::int64_cref get_total_vol() const;
		mfast::int64_cref try_get_total_vol() const;
		mfast::int64_cref get_total_turnover() const;
		mfast::int64_cref try_get_total_turnover() const;
		mfast::int32_cref get_pre_close_index() const;
		mfast::int32_cref try_get_pre_close_index() const;

	};


	typedef mfast::make_aggregate_mref<stock_TdfIndexl2_cref>
	stock_TdfIndexl2_mref_base;
	class stock_TdfIndexl2_mref
		: public stock_TdfIndexl2_mref_base
	{
		typedef stock_TdfIndexl2_mref_base base_type;
	public:
		typedef mfast::template_instruction_ex<stock_TdfIndexl2_cref> instruction_type;
		typedef const instruction_type *instruction_cptr;
		stock_TdfIndexl2_mref();
		template <typename T>
		stock_TdfIndexl2_mref(
			mfast::allocator       *alloc,
			typename std::enable_if<std::is_same<typename T::cref_type, stock_TdfIndexl2_cref>::value, mfast::value_storage *>::type
			storage,
			const T *instruction);

		stock_TdfIndexl2_mref(const mfast::message_mref &other);

		operator mfast::message_mref();
		explicit stock_TdfIndexl2_mref(const mfast::field_mref_base &other);

		template <typename Visitor>
		void accept(Visitor &v);

		mfast::int32_mref set_version() const;
		mfast::ascii_string_mref set_WIND_code() const;
		mfast::ascii_string_mref set_origin_code() const;
		mfast::int32_mref set_action_day() const;
		mfast::int32_mref set_trading_day() const;
		mfast::int32_mref set_time() const;
		mfast::int32_mref set_open_index() const;
		mfast::int32_mref set_highest_index() const;
		mfast::int32_mref set_lowest_index() const;
		mfast::int32_mref set_last_index() const;
		mfast::int64_mref set_total_vol() const;
		mfast::int64_mref set_total_turnover() const;
		mfast::int32_mref set_pre_close_index() const;
	};

	class stock_TdfIndexl2
		: private mfast::value_storage_array<13>
		, public mfast::message_type
	{
		typedef mfast::message_type base_type;
	public:
		enum {
			the_id = 14
		};
		typedef mfast::template_instruction_ex<stock_TdfIndexl2_cref> instruction_type;

		typedef mfast::make_message_cref<stock_TdfIndexl2_cref, instruction_type>
		cref_type;
		typedef mfast::make_message_mref<stock_TdfIndexl2_mref, instruction_type>
		mref_type;
		stock_TdfIndexl2(
			mfast::allocator *alloc=mfast::malloc_allocator::instance());
		stock_TdfIndexl2(
			const stock_TdfIndexl2_cref &other,
			mfast::allocator *alloc=mfast::malloc_allocator::instance());
		cref_type ref() const;
		cref_type cref() const;
		mref_type ref();
		mref_type mref();
		static const instruction_type *instruction();
	private:
		stock_TdfIndexl2(const stock_TdfIndexl2 &);
		stock_TdfIndexl2 &operator = (const stock_TdfIndexl2 &);
	};


	struct  templates_description
			: mfast::templates_description {
		typedef std::tuple<cffexl2,
				dcel2_MDBestAndDeep,
				dcel2_MArbi,
				dcel2_MD10Entrust,
				dcel2_MDOrderStat,
				dcel2_MDRTPrice,
				dcel2_MDMatchPV,
				zcel2_Snapshot,
				zcel2_CMB,
				level1,
				stock_TdfMarketl2,
				stock_TdfIndexl2> types;
		templates_description();
		static const templates_description *instance();
	};

	inline const templates_description *description()
	{
		return templates_description::instance();
	}

#include "rq_fast.inl"
}

#endif //__RQ_FAST_H__
